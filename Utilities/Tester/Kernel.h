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

namespace NVL_AI
{
	class Kernel
	{
	private:
		Mat _weights;
	public:
		Kernel(const string& path);
		double Evaluate(Mat& image);
		inline Mat& GetWeights() { return _weights; }
	};
}