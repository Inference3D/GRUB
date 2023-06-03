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
	public:
		PathHelper(const string& database, const string& dataset);

		string GetRawFolder();
		string GetMetaFolder();

	private:
		string GetPath(const string& folder);
	};
}
