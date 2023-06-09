//--------------------------------------------------
// Add the logic to assist with the construction of the paths within the system
//
// @author: Wild Boar
//
// @date: 2023-03-28
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/FileUtils.h>

namespace NVL_App
{
	class PathHelper
	{
	private:
		string _database;
		string _dataset;
		string _basePath;
	public:
		PathHelper(const string& database, const string& dataset);

		string GetTestFolder();
		string GetMetaFolder();

		inline string& GetDatabase() { return _database; }
		inline string& GetDataset() { return _dataset; }
		inline string& GetBasePath() { return _basePath; }

	private:
		string GetPath(const string& folder);
	};
}
