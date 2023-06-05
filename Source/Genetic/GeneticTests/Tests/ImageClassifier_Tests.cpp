//--------------------------------------------------
// Unit Tests for class ImageClassifier
//
// @author: Wild Boar
//
// @date: 2023-06-05
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/Formatter.h>

#include <GeneticLib/Instance/ImageClassifier/ImageClassifier.h>
using namespace NVL_App;

#include "../Helpers/SequenceGenerator.h"

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
Mat InvertImage(Mat& image);
unique_ptr<Solution> BuildSolution(int id, Mat& image);
void CreateDatabase(PathHelper& pathHelper, vector<TestImage>& data);

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm that evaluation is working correctly
 */
TEST(ImageClassifier_Test, evaluation_test)
{
	// Create the test images
	Mat image_1 = Mat_<uchar>::zeros(100, 100); rectangle(image_1, Rect(10, 10, 80, 80), Scalar(1), FILLED);
	Mat image_2 = InvertImage(image_1);
	auto data = vector<TestImage> { TestImage(0, image_1, 1), TestImage(1, image_2, 0) };

	// Place the images into a database + Create an image loader
	auto helper = PathHelper("database", "classifier_tests"); CreateDatabase(helper, data);
	auto loader = ImageLoader(helper, "classes.txt");

	// Generate a solution
	auto solution = BuildSolution(0, image_2);

	// Perform an evaluation
	auto evaluator = ImageClassifier(&loader);
	auto error = evaluator.GetError(solution.get());

	// Check that the error is what was expected
	ASSERT_EQ(error[0], 3600);
	ASSERT_EQ(error[1], 0);
}

/**
 * @brief Confirm that the representation is correct
 */
TEST(ImageClassifier_Test, string_representation)
{
	FAIL() << "Not implemented";

	// Setup

	// Execute

	// Confirm

	// Teardown
}

/**
 * @brief Confirm the solution generation logic
 */
TEST(ImageClassifier_Test, solution_generation)
{
	FAIL() << "Not implemented";

	// Setup

	// Execute

	// Confirm

	// Teardown
}

//--------------------------------------------------
// Invert Image
//--------------------------------------------------

/**
 * @brief Add the logic to invert an image
 * @param image The image that we are inverting
 * @return Mat The resultant image
 */
Mat InvertImage(Mat& image) 
{
	Mat result = Mat_<uchar>(image.size());

	for (auto row = 0; row < image.rows; row++) 
	{
		for (auto column = 0; column < image.cols; column++) 
		{
			auto index = column + row * image.cols;
			result.data[index] = image.data[index] == 0 ? 1 : 0;
		}
	}

	return result;
}

/**
 * @brief Build the solution
 * @param id An identifier for the solution that we are building
 * @param image The image that we are developing
 * @return unique_ptr<Solution> 
 */
unique_ptr<Solution> BuildSolution(int id, Mat& image) 
{
	// Put the image data into a solution
	auto dna = vector<int>(); auto pixelCount = image.cols * image.rows;
	for (auto i = 0; i < pixelCount; i++) dna.push_back(image.data[i]);
	
	// Add the extra end parameters
	dna.push_back(1); // The scale factor
	dna.push_back(0); // The offset

	// Return the result
	return unique_ptr<Solution>(new Solution(id, dna));
}

/**
 * @brief Generate a database for the images
 * @param pathHelper The path helper
 * @param data The data that we are going to be storing into the database
 */
void CreateDatabase(PathHelper& pathHelper, vector<TestImage>& data) 
{
	// Remove the "old" database
	if (NVLib::FileUtils::Exists(pathHelper.GetDatabase())) NVLib::FileUtils::RemoveAll(pathHelper.GetDatabase());

	// Create a new dataset that we are dealing with
	NVLib::FileUtils::AddFolders(pathHelper.GetDatabase()); 
	NVLib::FileUtils::AddFolder(pathHelper.GetBasePath());
	NVLib::FileUtils::AddFolder(pathHelper.GetRawFolder());
	NVLib::FileUtils::AddFolder(pathHelper.GetMetaFolder());

	// Create the classification
	auto path = NVLib::FileUtils::PathCombine(pathHelper.GetMetaFolder(), "classes.txt");
	auto writer = ofstream(path);

	// Loop thru data points
	for (auto& point : data) 
	{
		auto imageName = (string)(NVLib::Formatter() << "image_" << setw(4) << setfill('0') << point.GetId() << ".png");
		auto path = NVLib::FileUtils::PathCombine(pathHelper.GetRawFolder(), imageName);
		imwrite(path, point.GetImage());
		writer << point.GetId() << "," << point.GetImageType() << endl;
	}

	writer.close();
}
