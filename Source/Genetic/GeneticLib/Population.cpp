//--------------------------------------------------
// Implementation of class Population
//
// @author: Wild Boar
//
// @date: 2023-06-03
//--------------------------------------------------

#include "Population.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Default Constructor
 */
Population::Population()
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Main Terminator
 */
Population::~Population()
{
	// Add removal logic
}

//--------------------------------------------------
// Add Solutions
//--------------------------------------------------

/**
 * @brief Add a solution
 * @param solution The solution that we are adding
 */
void Population::AddSolution(Solution * solution)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Get Count
//--------------------------------------------------

/**
 * @brief Retrieve the count of solutions
 * @return int Returns a int
 */
int Population::GetSolutionCount()
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Get Top Solution
//--------------------------------------------------

/**
 * @brief Retrieve the n solutions
 * @param number The number of top solutions that we want
 * @param result The resultant solutions
 */
void Population::GetTopSolutions(int number, vector<Solution *>& result)
{
	throw runtime_error("Not implemented");
}
