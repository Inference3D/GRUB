//--------------------------------------------------
// Unit Tests for class FilterClassifier
//
// @author: Wild Boar
//
// @date: 2023-06-04
//--------------------------------------------------

#include <gtest/gtest.h>

#include <GeneticLib/FilterClassifier.h>
using namespace NVL_App;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Test that the evaluation was predictable
 */
TEST(FilterClassifier_Test, evaluation_test)
{
	// Create the image
	Mat image = Mat_<uchar>::zeros(100, 100);
	rectangle(image, Rect(30, 30, 40, 40), Scalar(255), FILLED);

	// Create the solution
	auto dna = vector<int>(); 
	for (auto i = 0; i < 100 * 100; i++) dna.push_back(4); 
	dna.push_back(255); dna.push_back(5);
	auto solution = Solution(1, dna);

	// Create a classifier
	auto classifier = FilterClassifier(&solution);

	// Verify the expected fire
	auto score = classifier.Evaluate(image); 
	ASSERT_EQ(score, 6405);
}