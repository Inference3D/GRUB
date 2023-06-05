//--------------------------------------------------
// Implementation of class FilterClassifier
//
// @author: Wild Boar
//
// @date: 2023-06-04
//--------------------------------------------------

#include "FilterClassifier.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param solution The solution that we are initializing from
 */
FilterClassifier::FilterClassifier(Solution * solution)
{
	// Determine the size
	auto count = solution->GetDna().size() - 2;
	auto width = sqrt(count);

	// Create the variable
	_kernel = Mat_<float>::zeros(width, width);
	auto link = (float *)_kernel.data;

	// Retrieve the scale variables
	auto scale = (float) solution->GetDna()[count];
	_offset = solution->GetDna()[count + 1];

	// Clear the DNA the variables
	auto pixelCount = _kernel.cols * _kernel.rows;
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
double FilterClassifier::Evaluate(Mat& image)
{
	Mat floatImage; image.convertTo(floatImage, CV_32F);
	Mat partial; multiply(_kernel, floatImage, partial);
	auto total = sum(partial);
	return total[0] + _offset;
}