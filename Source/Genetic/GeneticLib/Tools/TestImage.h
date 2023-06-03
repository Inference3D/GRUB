//--------------------------------------------------
// An image for testing/training the AI
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

namespace NVL_Lib
{
	class TestImage
	{
	private:
		int _id;
		Mat _image;
		int _imageType;

	public:
		TestImage(int id, Mat& image, int imageType) :
			_id(id), _image(image), _imageType(imageType) {}

		inline int& GetId() { return _id; }
		inline Mat& GetImage() { return _image; }
		inline int& GetImageType() { return _imageType; }
	};
}