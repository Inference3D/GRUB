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
 * @param solution The solution that we are initializing from
 */
Kernel::Kernel(Solution * solution)
{
	// Determine the size
	auto count = solution->GetDna().size() - 2;
	auto width = sqrt(count);

	// Create the variable
	_weights = Mat_<float>::zeros(width, width);
	auto link = (float *)_weights.data;

	// Retrieve the scale variables
	auto scale = (float) solution->GetDna()[count];

	// Clear the DNA the variables
	auto pixelCount = _weights.cols * _weights.rows;
	for (auto i = 0; i < pixelCount; i++) link[i] = solution->GetDna()[i] / scale;
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