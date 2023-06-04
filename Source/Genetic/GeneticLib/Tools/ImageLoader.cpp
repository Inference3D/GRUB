//--------------------------------------------------
// Implementation of class ImageLoader
//
// @author: Wild Boar
//
// @date: 2023-06-04
//--------------------------------------------------

#include "ImageLoader.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param pathHelper A helper for loading variables
 * @param lookupName The name of the lookup file that we want to use
 */
ImageLoader::ImageLoader(PathHelper& pathHelper, const string& lookupName)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Next
//--------------------------------------------------

/**
 * @brief Retrieve the next image within the list
 * @return unique_ptr<TestImage> Returns a unique_ptr<TestImage>
 */
unique_ptr<TestImage> ImageLoader::Next()
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Reset
//--------------------------------------------------

/**
 * @brief Reset the pointer to the current image
 */
void ImageLoader::Reset()
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Image Count
//--------------------------------------------------

/**
 * @brief Retrieve the number of images
 * @return int Returns a int
 */
int ImageLoader::GetCount()
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Helpers
//--------------------------------------------------

/**
 * @brief Retrieve the index image from the path
 * @param path The path that we are trying to extract the value for
 * @return int Returns a int
 */
int ImageLoader::GetImageIndex(const string& path)
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Load the class lookup from disk
 * @param folder The folder that we are looking up
 * @param lookupName The name of the lookup file that we are using
 * @return unordered_map<int, int> Returns a unordered_map<int, int>
 */
unordered_map<int, int> ImageLoader::LoadLookup(const string& folder, const string& lookupName)
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Retrieve the list of image files within the folder
 * @param folder The folder that we are retrieving files from
 * @return vector<string> Returns a vector<string>
 */
vector<string> ImageLoader::GetFiles(const string& folder)
{
	throw runtime_error("Not implemented");
}
