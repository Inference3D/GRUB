//--------------------------------------------------
// Unit Tests for class Population
//
// @author: Wild Boar
//
// @date: 2023-06-03
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/StringUtils.h>

#include <GeneticLib/Population.h>
using namespace NVL_App;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
Solution * CreateSolution(int id, const string dna, double score); 

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Retrieve the top solutions
 */
TEST(Population_Test, get_top_solutions)
{
	// Create a population
	auto population = Population();

	// Add some solutions to the population
	population.AddSolution(CreateSolution(1, "1,2,3", 5));
	population.AddSolution(CreateSolution(2, "1,2,3", 3));
	population.AddSolution(CreateSolution(3, "1,2,3", 7));
	population.AddSolution(CreateSolution(4, "1,2,3", 9));
	population.AddSolution(CreateSolution(5, "1,2,3", 2));
	population.AddSolution(CreateSolution(6, "1,2,3", 8));

	// Verify the solution count
	ASSERT_EQ(population.GetSolutionCount(), 6);

	// Retrieve the top 3 solutions
	auto top = vector<Solution *>(); population.GetTopSolutions(3, top);

	// Verify the top solutions
	ASSERT_EQ(top[0]->GetId(), 5);
	ASSERT_EQ(top[1]->GetId(), 2);
	ASSERT_EQ(top[2]->GetId(), 1);
}

//--------------------------------------------------
// Helper Methods
//--------------------------------------------------

/**
 * @brief Create a test solution
 * @param id The identifier of the solution
 * @param dna The DNA associated with the solution
 * @param score The score that we want for the solution
 * @return Solution The created solution model
 */
Solution * CreateSolution(int id, const string dna, double score) 
{
	// Convert the DNA into a vector
	auto dnaVector = vector<int>(); auto parts = vector<string>();
	NVLib::StringUtils::Split(dna, ',', parts);
	for (auto& part : parts) dnaVector.push_back(NVLib::StringUtils::String2Int(part));

	// Create the solution entity
	auto result = new Solution(id, dnaVector);

	// Set the score associated with the result
	result->SetError(score);

	// Return the result
	return result;
}
