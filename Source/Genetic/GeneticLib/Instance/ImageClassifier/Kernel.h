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
using namespace NVL_App;

namespace NVL_AI
{
	class Kernel
	{
	private:
		Mat _weights;
		double _offset;
	public:
		Kernel(Solution * solution);

		double Evaluate(Mat& image);

		inline Mat& GetWeights() { return _weights; }
		inline double& GetOffset() { return _offset; }
	};
}