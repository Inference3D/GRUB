//--------------------------------------------------
// Startup code module
//
// @author: Wild Boar
//
// @date: 2023-06-08
//--------------------------------------------------

#include <iostream>
using namespace std;

#include <NVLib/Logger.h>
#include <NVLib/Parameters/Parameters.h>

#include <opencv2/opencv.hpp>
using namespace cv;

#include "ArgReader.h"
#include "PathHelper.h"
#include "ImageLoader.h"
#include "Kernel.h"

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void Run(NVLib::Parameters * parameters);

//--------------------------------------------------
// Execution Logic
//--------------------------------------------------

/**
 * Main entry point into the application
 * @param parameters The input parameters
 */
void Run(NVLib::Parameters * parameters) 
{
    // Verify that we have some input parameters
    if (parameters == nullptr) return; auto logger = NVLib::Logger(1);

    logger.StartApplication();

    logger.Log(1, "Load the input arguments");
    auto database = NVL_Utils::ArgReader::ReadString(parameters, "database");
    auto dataset = NVL_Utils::ArgReader::ReadString(parameters, "dataset");
    auto model = NVL_Utils::ArgReader::ReadString(parameters, "model");
    auto helper = NVL_App::PathHelper(database, dataset);

    logger.Log(1, "Create the kernel");
    auto kernelPath = NVLib::FileUtils::PathCombine(helper.GetModelFolder(), model);
    auto kernel = NVL_AI::Kernel(kernelPath);

    logger.Log(1, "Create an image loader");
    auto loader = NVL_App::ImageLoader(helper, "test.txt");

    while(true) 
    {
        auto testPoint = loader.Next();
        auto score = kernel.Evaluate(testPoint->GetImage());

        auto min = abs(score); auto max = abs(100-score);
        auto detection = max < min ? 1 : 0;
        auto success = detection == testPoint->GetImageType();
        
        if (success) logger.Log(1, "%i. SUCCESS: %f", testPoint->GetId(), score);
        else logger.Log(1, "%i. FAIL: %f", testPoint->GetId(), score);
    }

    logger.StopApplication();    
}

//--------------------------------------------------
// Entry Point
//--------------------------------------------------

/**
 * Main Method
 * @param argc The count of the incoming arguments
 * @param argv The number of incoming arguments
 * @return SUCCESS and FAILURE
 */
int main(int argc, char ** argv) 
{
    NVLib::Parameters * parameters = nullptr;

    try
    {
        parameters = NVL_Utils::ArgReader::GetParameters(argc, argv);
        Run(parameters);
    }
    catch (runtime_error exception)
    {
        cerr << "Error: " << exception.what() << endl;
        exit(EXIT_FAILURE);
    }
    catch (string exception)
    {
        cerr << "Error: " << exception << endl;
        exit(EXIT_FAILURE);
    }

    if (parameters != nullptr) delete parameters;

    return EXIT_SUCCESS;
}
