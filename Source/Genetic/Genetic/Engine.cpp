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
    auto errorType = ArgUtils::GetInteger(parameters, "error_type");
    auto maxIterations = ArgUtils::GetInteger(parameters, "max_iterations");
    _learningArguments = new GeneticParameters(populationSize, tournamentSize, mutationProbability, eliteCount, errorType, maxIterations);

    logger->Log(1, "Setting up an image loader");
    _loader = new ImageLoader(helper, classFile);

    logger->Log(1, "Creating a learning wrapper");
    _learningWrapper = new NVL_AI::LearnWrapper(_loader);

    logger->Log(1, "Creating an instance of a given learner");
    _learner = new GeneticEngine(_learningArguments, _learningWrapper);
}

/**
 * Main Terminator 
 */
Engine::~Engine() 
{
    delete _parameters;
    delete _loader;
    delete _learningArguments;
    delete _learningWrapper;
    delete _learner;
}

//--------------------------------------------------
// Execution Entry Point
//--------------------------------------------------

/**
 * Entry point function
 */
void Engine::Run()
{
    _logger->Log(1, "Generating initial solutions");
    _learner->Initialize();

    _logger->Log(1, "Creating a graph series");
    auto series = NVLib::GraphSeries("Learner", Vec3i(0,0,255), vector<Point2d>());
    auto graph = NVLib::Graph("GLearner", "Score", "Epoch");
    graph.AddSeries(series);

    _logger->StartFunction("Solution Refinement");
    for (auto i = 0; i < _learningArguments->GetMaxIterations(); i++) 
    {
        _logger->Log(1, "Processing Epoch: %i", i);

        _logger->Log(1, "Evaluating Solutions");
        auto bestSolution = _learner->EvaluateSolutions();
        _logger->Log(1, "Best Score: %f", bestSolution->GetError());

        _logger->Log(1, "Writing graph");
        graph.GetSeries()[0].GetValues().push_back(Point2d(i, bestSolution->GetError()));
        Mat graphImage = graph.Render(Size(1000,1000)); imwrite("graph.png", graphImage);

        if (bestSolution->GetError() == 0) 
        {
            _logger->Log(1, "The problem appears to have been solved! Quitting...");
            break;
        }

        _logger->Log(1, "Spawning the next generation");
        _learner->SpawnNew();
    }

    _logger->StopFunction();

    _logger->Log(1, "Evaluate the final generation");
    auto bestSolution = _learner->EvaluateSolutions();

    _logger->Log(1, "Final best solution score: %f", bestSolution->GetError());

    ////////////////////// TESTING //////////////////////////////////////////////

    auto kernel = NVL_AI::Kernel(bestSolution);
    _loader->Reset();

    while (true) 
    {
        auto dataPoint = _loader->Next();
        if (dataPoint.get() == nullptr) break;
        auto score = kernel.Evaluate(dataPoint->GetImage());
        _logger->Log(1, "Score %i: %f", dataPoint->GetId(), score);
    }

    ////////////////////// TESTING //////////////////////////////////////////////

    _logger->Log(1, "Writing result to disk");
    imwrite("solution.tiff", kernel.GetWeights());
}
