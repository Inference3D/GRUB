//--------------------------------------------------
// Unit Tests for class ImageLoader
//
// @author: Wild Boar
//
// @date: 2023-06-04
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/Formatter.h>
#include <NVLib/FileUtils.h>

#include <GeneticLib/Tools/ImageLoader.h>
using namespace NVL_App;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void GenerateDatabase(PathHelper& pathHelper);

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Determines that we can cycle thru a set of images within the database
 */
TEST(ImageLoader_Test, test_image_cycle)
{
	// Setup the database
	auto helper = PathHelper("database", "test"); GenerateDatabase(helper);

	// Execute
	auto loader = ImageLoader(helper, "classes.txt");
	ASSERT_EQ(loader.GetCount(), 6);

	// Check the individual elements
	for (auto i = 0; i < 7; i++) 
	{
		auto dataPoint = loader.Next();

		if (i == 0) ASSERT_EQ(dataPoint->GetImageType(), 1);
		else if (i == 6) 
		{
			ASSERT_EQ(dataPoint.get(), nullptr);
			continue;
		}
		else ASSERT_EQ(dataPoint->GetImageType(), 0);

		ASSERT_EQ(dataPoint->GetId(), i);

		ASSERT_EQ(dataPoint->GetImage().rows, 100);
		ASSERT_EQ(dataPoint->GetImage().cols, 100);
	}
}

//--------------------------------------------------
// Generate a test database
//--------------------------------------------------

/**
 * @brief Generate a database
 * @param pathHelper The path that we are dealing with
 */
void GenerateDatabase(PathHelper& pathHelper) 
{
	// Remove the "old" database
	if (NVLib::FileUtils::Exists(pathHelper.GetDatabase())) NVLib::FileUtils::RemoveAll(pathHelper.GetDatabase());

	// Create a new dataset that we are dealing with
	NVLib::FileUtils::AddFolders(pathHelper.GetDatabase()); 
	NVLib::FileUtils::AddFolder(pathHelper.GetBasePath());
	NVLib::FileUtils::AddFolder(pathHelper.GetRawFolder());
	NVLib::FileUtils::AddFolder(pathHelper.GetMetaFolder());

	// Create some test images
	for (auto i = 0; i < 6; i++) 
	{
		Mat image = Mat_<uchar>::zeros(100, 100);
		putText(image, NVLib::StringUtils::Int2String(i), Point(30,70), FONT_HERSHEY_COMPLEX, 2, Scalar(255));
		auto imageName = (string)(NVLib::Formatter() << "image_" << setw(4) << setfill('0') << i << ".png");
		auto path = NVLib::FileUtils::PathCombine(pathHelper.GetRawFolder(), imageName);
		imwrite(path, image);
	}

	// Create the classification
	auto path = NVLib::FileUtils::PathCombine(pathHelper.GetMetaFolder(), "classes.txt");
	auto writer = ofstream(path);

	for (auto i = 0; i < 6; i++) 
	{
		if (i == 0) writer << i << ",1" << endl;
		else writer << i << ",0" << endl;
	}

	writer.close();
}