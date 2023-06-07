//--------------------------------------------------
// Startup code module
//
// @author: Wild Boar
//
// @date: 2023-06-07
//--------------------------------------------------

#include <iostream>
using namespace std;

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
    if (parameters == nullptr) return;

    // Load the parameters into variables
    auto inputFolder = NVL_Utils::ArgReader::ReadString(parameters, "input");
    auto outputFolder = NVL_Utils::ArgReader::ReadString(parameters, "output");
    auto filename = NVL_Utils::ArgReader::ReadString(parameters, "filename");
    auto count = NVL_Utils::ArgReader::ReadInteger(parameters, "count");

    cout << "Hello World" << endl;
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
