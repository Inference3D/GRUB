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

    logger->Log(1, "Retrieving input parameters");
    auto database = ArgUtils::GetString(parameters, "database");
    auto dataset = ArgUtils::GetString(parameters, "dataset");
    auto classFile = ArgUtils::GetString(parameters, "class_file");
    auto helper = PathHelper(database, dataset);

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
