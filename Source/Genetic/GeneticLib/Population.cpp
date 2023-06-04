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
	// Extra implementation goes here
}

/**
 * @brief Main Terminator
 */
Population::~Population()
{
	for (auto solution : _solutions) delete solution;
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
	_solutions.push_back(solution);
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
	return (int) _solutions.size();
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
	auto bestScore = -1.0; result.clear();

	for (auto solution : _solutions) 
	{
		if (result.size() == 0) result.push_back(solution);
		else 
		{
			auto added = false;
			for (auto i = 0; i < result.size(); i++) 
			{
				if (result[i]->GetError() > solution->GetError()) 
				{
					result.insert(result.begin() + i, solution);
					added = true;
					break;
				}
			}

			if (result.size() > number) result.erase(result.begin() + (int)(result.size() - 1));
			else if (result.size() < number && !added) result.push_back(solution);
		}
	}
}
