//--------------------------------------------------
// Implementation code for the Engine
//
// @author: Wild Boar
//
// @date: 2023-06-02
//--------------------------------------------------

#include "Engine.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructor and Terminator
//--------------------------------------------------

/**
 * Main Constructor
 * @param logger The logger that we are using for the system
 * @param parameters The input parameters
 */
Engine::Engine(NVLib::Logger* logger, NVLib::Parameters* parameters) 
{
    _logger = logger; _parameters = parameters;

    logger->Log(1, "Retrieving data input parameters");
    auto database = ArgUtils::GetString(parameters, "database");
    auto dataset = ArgUtils::GetString(parameters, "dataset");
    auto classFile = ArgUtils::GetString(parameters, "class_file");
    auto helper = PathHelper(database, dataset);

    logger->Log(1, "Retrieving inputs about the learning");
    auto populationSize = ArgUtils::GetInteger(parameters, "population_size");
    auto tournamentSize = ArgUtils::GetInteger(parameters, "tournament_size");
    auto mutationProbability = ArgUtils::GetDouble(parameters, "mutation_probability");
    auto eliteCount = ArgUtils::GetInteger(parameters, "elite_count");
    _learningArguments = new GeneticParameters(populationSize, tournamentSize, mutationProbability, eliteCount);

    logger->Log(1, "Setting up an image loader");
    _loader = new ImageLoader(helper, classFile);
}

/**
 * Main Terminator 
 */
Engine::~Engine() 
{
    delete _parameters;
    delete _loader;
    delete _learningArguments;
}

//--------------------------------------------------
// Execution Entry Point
//--------------------------------------------------

/**
 * Entry point function
 */
void Engine::Run()
{
    while (true) 
    {
        auto dataPoint = _loader->Next();
        if (dataPoint.get() == nullptr) break;
        imshow("image", dataPoint->GetImage()); waitKey();
    }
}
