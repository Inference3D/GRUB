//--------------------------------------------------
// A tool for loading test/training images
//
// @author: Wild Boar
//
// @date: 2023-06-04
//--------------------------------------------------

#pragma once

#include <unordered_map>
#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include <NVLib/FileUtils.h>
#include "PathHelper.h"
#include "TestImage.h"

namespace NVL_App
{
	class ImageLoader
	{
	private:
		vector<string> _paths;
		vector<int> _classes;
		int _position;
	public:
		ImageLoader(PathHelper& pathHelper, const string& lookupName);

		unique_ptr<TestImage> Next();
		void Reset();
		int GetCount();

		inline vector<string>& GetPaths() { return _paths; }
		inline vector<int>& GetClasses() { return _classes; }
		inline int& GetPosition() { return _position; }

	private:
		int GetImageIndex(const string& path);
		unordered_map<int, int> LoadLookup(const string& folder, const string& lookupName);
		vector<string> GetFiles(const string& folder);
	};
}