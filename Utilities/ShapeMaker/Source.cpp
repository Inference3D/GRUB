//--------------------------------------------------
// Startup code module
//
// @author: Wild Boar
//
// @date: 2023-06-02
//--------------------------------------------------

#include <iostream>
using namespace std;

#include <NVLib/Logger.h>
#include <NVLib/Parameters/Parameters.h>

#include <opencv2/opencv.hpp>
using namespace cv;

#include "ArgReader.h"

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

    logger.Log(1, "Retrieve input arguments for the application");
    auto blockSize = NVL_Utils::ArgReader::ReadInteger(parameters, "block_size");
    auto wCount = NVL_Utils::ArgReader::ReadInteger(parameters, "w_count");
    auto hCount = NVL_Utils::ArgReader::ReadInteger(parameters, "h_count");
    auto useRotation = NVL_Utils::ArgReader::ReadInteger(parameters, "use_rot");

    logger.Log(1, "Generate a base image");
    Mat image = Mat_<Vec3b>(blockSize * hCount, blockSize * wCount); image.setTo(Vec3b(255, 255, 255));

    logger.Log(1, "Saving the result to disk");
    imwrite("result.png", image);

    logger.StartApplication();
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
