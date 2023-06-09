//--------------------------------------------------
// Implementation of class PathHelper
//
// @author: Wild Boar
//
// @date: 2023-03-28
//--------------------------------------------------

#include "PathHelper.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param database The database that we are using
 * @param dataset The dataset that we are working in within the database
 */
PathHelper::PathHelper(const string& database, const string& dataset) : _database(database), _dataset(dataset)
{
	_basePath = NVLib::FileUtils::PathCombine(database, dataset);
}

//--------------------------------------------------
// Folder Generator
//--------------------------------------------------

/**
 * @brief Generate the path to the "raw" (images) folder
 * @return string Returns a string
 */
string PathHelper::GetTestFolder()
{
	return GetPath("test");
}

/**
 * @brief Generate the pat to the "meta" (meta data) folder
 * @return string Returns a string
 */
string PathHelper::GetMetaFolder()
{
	return GetPath("meta");
}

//--------------------------------------------------
// Helpers
//--------------------------------------------------

/**
 * @brief Creates a path within the system
 * @param folder Generates a path to a new folder within the system
 * @return string Returns a string
 */
string PathHelper::GetPath(const string& folder)
{
	return NVLib::FileUtils::PathCombine(_basePath, folder);
}