//--------------------------------------------------
// The implementation of a filter classifier
//
// @author: Wild Boar
//
// @date: 2023-06-04
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include "Solution.h"

namespace NVL_App
{
	class FilterClassifier
	{
	private:
		Mat _kernel;
		double _offset;
	public:
		FilterClassifier(Solution * solution);

		double Evaluate(Mat& image);

		inline Mat& GetKernel() { return _kernel; }
		inline double& GetOffset() { return _offset; }
	};
}