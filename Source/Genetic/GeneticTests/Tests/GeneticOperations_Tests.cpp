//--------------------------------------------------
// Unit Tests for class GeneticOperations
//
// @author: Wild Boar
//
// @date: 2023-06-06
//--------------------------------------------------

#include <gtest/gtest.h>

#include <GeneticLib/Instance/ImageClassifier/LearnWrapper.h>

#include <GeneticLib/GeneticOperations.h>
using namespace NVL_App;

#include "../Helpers/SequenceGenerator.h"

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
Solution * MakeSolution(int id, const vector<int>& dna, double error);

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm the tournament select operation
 */
TEST(GeneticOperations_Test, tournament_select)
{
	// Build the given population variable
	auto population = Population();
	population.AddSolution(MakeSolution( 1, vector<int> { 1,  2,  3}, 5)); // 0
	population.AddSolution(MakeSolution( 2, vector<int> { 4,  5,  6}, 2)); // 1
	population.AddSolution(MakeSolution( 3, vector<int> { 7,  8,  9}, 1)); // 2
	population.AddSolution(MakeSolution( 4, vector<int> {10, 11, 12}, 3)); // 3
	population.AddSolution(MakeSolution( 5, vector<int> {13, 14, 15}, 9)); // 4
	population.AddSolution(MakeSolution( 6, vector<int> {15, 16, 17}, 7)); // 5
	population.AddSolution(MakeSolution( 7, vector<int> {18, 19, 20}, 2)); // 6
	population.AddSolution(MakeSolution( 8, vector<int> {21, 22, 23}, 6)); // 7
	population.AddSolution(MakeSolution( 9, vector<int> {24, 25, 26}, 8)); // 8
	population.AddSolution(MakeSolution(10, vector<int> {27, 28, 29}, 5)); // 9

	// Build a sequence generator
	auto generator = SequenceGenerator(vector<int> { 1, 7, 3, 2, 1 });

	// Create an instance engine
	auto engine = NVL_AI::LearnWrapper(nullptr);

	// Create a utilities variable
	auto utility = GeneticOperations(&engine, &generator);

	// Perform the actual tournament selection
	auto solution = utility.Select(&population, 5);

	// Verify that the response was the one that was expected
	ASSERT_EQ(solution->GetId(), 3);
	ASSERT_EQ(solution->GetError(), 1);	
}

//--------------------------------------------------
// Add a solution
//--------------------------------------------------

/**
 * @brief Add the logic to generate a given solution
 * @param id The identifier associated with the solution
 * @param dna The DNA signature of the given solution
 * @param error The error associated with the solution
 * @return Solution* The solution itself
 */
Solution * MakeSolution(int id, const vector<int>& dna, double error)
{
	auto result = new Solution(id, dna); 
	result->SetError(error);
	return result;
}