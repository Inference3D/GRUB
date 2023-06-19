//--------------------------------------------------
// Implementation of class Kernel
//
// @author: Wild Boar
//
// @date: 2023-06-04
//--------------------------------------------------

#include "Kernel.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param path The path that we are loading
 */
Kernel::Kernel(const string& path)
{
	_weights = imread(path, IMREAD_UNCHANGED);
}

//--------------------------------------------------
// Evaluation
//--------------------------------------------------

/**
 * @brief Perform the evaluate
 * @param image The image that we are matching
 * @return double Returns a double
 */
double Kernel::Evaluate(Mat& image)
{
	Mat floatImage; image.convertTo(floatImage, CV_32F);
	Mat partial; multiply(_weights, floatImage, partial);
	auto total = sum(partial);
	return abs(total[0]);
}