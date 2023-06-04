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
ImageLoader::ImageLoader(PathHelper& pathHelper, const string& lookupName) : _position(0)
{
	_paths = GetFiles(pathHelper.GetRawFolder());
	_classes = LoadLookup(pathHelper.GetMetaFolder(), lookupName);
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
	// Get and valid the index
	auto index = _position++; if (index >= _paths.size()) return unique_ptr<TestImage>(nullptr);

	auto id = GetImageIndex(_paths[index]);
	Mat image = imread(_paths[index]);

	if (_classes.find(id) == _classes.end()) return unique_ptr<TestImage>(nullptr);
	auto imageType = _classes[id];
	if (imageType < 0) return unique_ptr<TestImage>(nullptr);

	return unique_ptr<TestImage>(new TestImage(id, image, imageType));
}

//--------------------------------------------------
// Reset
//--------------------------------------------------

/**
 * @brief Reset the pointer to the current image
 */
void ImageLoader::Reset()
{
	_position = 0;
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
	return (int) _paths.size();
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
	auto fileName = NVLib::FileUtils::GetFileName(path);
	auto fileName_no_ext = NVLib::FileUtils::GetNameWithoutExtension(fileName);
	auto parts = vector<string>(); NVLib::StringUtils::Split(fileName_no_ext, '_', parts);
	if (parts.size() != 2) return -1;
	auto index = NVLib::StringUtils::String2Int(parts[1]);
	return index;
}

/**
 * @brief Load the class lookup from disk
 * @param folder The folder that we are looking up
 * @param lookupName The name of the lookup file that we are using
 * @return unordered_map<int, int> Returns a unordered_map<int, int>
 */
unordered_map<int, int> ImageLoader::LoadLookup(const string& folder, const string& lookupName)
{
	// The result that we dealing 
	auto result = unordered_map<int, int>();

	// Open the reader
	auto path = NVLib::FileUtils::PathCombine(folder, lookupName);
	auto reader = ifstream(path); if (!reader.is_open()) throw runtime_error("Unable for open: " + path);

	// Read the lines
	while (true) 
	{
		auto line = string();
		getline(reader, line); if (line == string()) break;
		auto parts = vector<string>(); NVLib::StringUtils::Split(line, ',', parts);
		auto index = NVLib::StringUtils::String2Int(parts[0]);
		auto classes = NVLib::StringUtils::String2Int(parts[1]);
		result[index] = classes;
	}

	// Close the file
	reader.close();

	// Return the result
	return result;
}

/**
 * @brief Retrieve the list of image files within the folder
 * @param folder The folder that we are retrieving files from
 * @return vector<string> Returns a vector<string>
 */
vector<string> ImageLoader::GetFiles(const string& folder)
{
	// Create a variable to hold the result
	auto result = vector<string>();
	
	// Get all the files within folder
	auto files = vector<string>(); NVLib::FileUtils::GetFileList(folder, files);

	// Filter out the "invalid" files
	for (auto& file : files) 
	{
		auto extension = NVLib::FileUtils::GetExtension(file);
		if (extension == "png") result.push_back(file);
	}

	// Return the result
	return result;
}