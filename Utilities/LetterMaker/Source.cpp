//--------------------------------------------------
// Startup code module
//
// @author: Wild Boar
//
// @date: 2023-06-07
//--------------------------------------------------

#include <fstream>
#include <iostream>
using namespace std;

#include <NVLib/Logger.h>
#include <NVLib/Formatter.h>
#include <NVLib/Parameters/Parameters.h>

#include <opencv2/opencv.hpp>
using namespace cv;

#include "ArgReader.h"
#include "PathHelper.h"

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

    logger.Log(1, "Load the parameters");
    auto database = NVL_Utils::ArgReader::ReadString(parameters, "database");
    auto dataset = NVL_Utils::ArgReader::ReadString(parameters, "dataset");
  
    // Create a path helper
    auto helper = NVL_App::PathHelper(database, dataset);

    logger.Log(1, "Rebuild the parameters");
    if (NVLib::FileUtils::Exists(helper.GetBasePath())) NVLib::FileUtils::RemoveAll(helper.GetBasePath());
    NVLib::FileUtils::AddFolders(helper.GetBasePath());
    NVLib::FileUtils::AddFolder(helper.GetMetaFolder());
    NVLib::FileUtils::AddFolder(helper.GetRawFolder());

    logger.Log(1, "Create a classes");
    auto classFile = NVLib::FileUtils::PathCombine(helper.GetMetaFolder(), "classes.txt");
    auto writer = ofstream(classFile);

    logger.Log(1, "Create an image set");
    for (auto value = 'A'; value <= 'Z'; value++) 
    {
        logger.Log(1, "Creating image: %c", value);

        writer << (int)(value - 'A') << "," << (value == 'A' ? 1 : 0) << endl;

        Mat image = Mat_<uchar>::zeros(100, 100);
		putText(image, NVLib::Formatter() << value, Point(30,70), FONT_HERSHEY_COMPLEX, 2, Scalar(255), 2);
		auto imageName = (string)(NVLib::Formatter() << "image_" << setw(4) << setfill('0') << (int)(value - 'A') << ".png");
		auto path = NVLib::FileUtils::PathCombine(helper.GetRawFolder(), imageName);
		imwrite(path, image);
    }

    logger.Log(1, "Free the result");
    writer.close();
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
