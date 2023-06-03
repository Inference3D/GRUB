//--------------------------------------------------
// Startup code module
//
// @author: Wild Boar
//
// @date: 2023-06-02
//--------------------------------------------------

#include <fstream>
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
void RenderTriangle(Mat& image, int blockSize, int wx, int wh);
void RenderCircle(Mat& image, int blockSize, int wx, int wh);
void RenderSquare(Mat& image, int blockSize, int wx, int wh);

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

    // logger.Log(1, "Generate a base image");
    // Mat image = Mat_<Vec3b>(blockSize * hCount, blockSize * wCount); image.setTo(Vec3b(255, 255, 255));

    // logger.Log(1, "Creating a truth map");
    // auto truthMap = vector<Point>();

    // logger.Log(1, "Generating shapes");
    // for (auto row = 0; row < hCount; row++) 
    // {
    //     for (auto column = 0; column < wCount; column++) 
    //     {
    //         auto selection = rand() % 3;

    //         if (selection == 0) { RenderTriangle(image, blockSize, column, row); truthMap.push_back(Point(column, row)); }
    //         else if (selection == 1) RenderCircle(image, blockSize, column, row);
    //         else RenderSquare(image, blockSize, column, row);
    //     }
    // }

    // logger.Log(1, "Saving the result to disk");
    // imwrite("result.png", image);

    // logger.Log(1, "Saving the truth map");
    // auto writer = ofstream("truthmap.txt");
    // for (auto& point : truthMap) writer << point.x << "," << point.y << endl;
    // writer.close();

    logger.Log(1, "Creating Triangle");
    Mat triangle = Mat_<Vec3b>(blockSize, blockSize); triangle.setTo(Vec3b(255, 255, 255)); RenderTriangle(triangle, blockSize, 0, 0);
    imwrite("image_0000.png", triangle);

    logger.Log(1, "Creating Circle");
    Mat Circle = Mat_<Vec3b>(blockSize, blockSize); Circle.setTo(Vec3b(255, 255, 255)); RenderCircle(Circle, blockSize, 0, 0);
    imwrite("image_0001.png", Circle);

    logger.Log(1, "Creating Square");
    Mat Square = Mat_<Vec3b>(blockSize, blockSize); Square.setTo(Vec3b(255, 255, 255)); RenderSquare(Square, blockSize, 0, 0);
    imwrite("image_0002.png", Square);


    logger.StartApplication();
}

//--------------------------------------------------
// Render Shapes
//--------------------------------------------------

/**
 * @brief Render a triangle
 * @param image The image that we are dealing with
 * @param blockSize The size of the block
 * @param wx The block width coordinate
 * @param wh The block height coordinate
 */
void RenderTriangle(Mat& image, int blockSize, int wx, int wh) 
{
    // Determine the buffer
    auto buffer = round(blockSize * 0.3);

    // Top Left location
    auto topX = wx * blockSize; auto topY = wh * blockSize;

    // Create a vector for points
    auto points = vector<Point>();

    // Point 1
    auto x1 = buffer + topX; auto y1 = (blockSize - buffer) + topY;
    points.push_back(Point(x1, y1));

    // Point 2
    auto x2 = (blockSize - buffer) + topX; auto y2 = (blockSize - buffer) + topY;
    points.push_back(Point(x2, y2));

    // Point 3
    auto x3 = (blockSize - 2 * buffer) * 0.5 + buffer + topX; auto y3 = buffer + topY;
    points.push_back(Point(x3, y3));

    // Render
    auto pp = vector< vector<Point> > { points };
    drawContours(image, pp, 0, Scalar(), FILLED);
}

/*
 * Add the logic to render  a circle
 * @param image The image that we are dealing with
 * @param blockSize The size of the block
 * @param wx The block width coordinate
 * @param wh The block height coordinate
 */
void RenderCircle(Mat& image, int blockSize, int wx, int wh) 
{
    // Determine the buffer
    auto buffer = round(blockSize * 0.3);

    // Top Left location
    auto topX = wx * blockSize; auto topY = wh * blockSize;

    // Find the radius
    auto radius = (blockSize - 2 * buffer) * 0.5;

    // Center
    auto cx = topX + radius + buffer;
    auto cy = topY + radius + buffer;

    // Render the circle
    circle(image, Point(cx, cy), radius, Scalar(), FILLED); 
}

/**
 * @brief Add the logic for rendering a square
 * @param image The image that we are rendering
 * @param blockSize The size of the block
 * @param wx The block x index
 * @param wh The block y index
 */
void RenderSquare(Mat& image, int blockSize, int wx, int wh) 
{
     // Determine the buffer
    auto buffer = round(blockSize * 0.3);

    // Top Left location
    auto topX = wx * blockSize + buffer; auto topY = wh * blockSize + buffer;

    // Find the radius
    auto length = (blockSize - buffer * 2);

    // Render the circle
    rectangle(image, Rect(Point(topX, topY), Size(length, length)), Scalar(), FILLED);
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
