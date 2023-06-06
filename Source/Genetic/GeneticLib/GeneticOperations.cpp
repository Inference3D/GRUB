//--------------------------------------------------
// Implementation of class GeneticOperations
//
// @author: Wild Boar
//
// @date: 2023-06-06
//--------------------------------------------------

#include "GeneticOperations.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Initializer Constructor
 * @param engine Initialize variable <engine>
 * @param generator Initialize variable <generator>
 */
GeneticOperations::GeneticOperations(InstanceEngineBase * engine, GeneratorBase * generator)
{
	_engine = engine;
	_generator = generator;
}

//--------------------------------------------------
// Create Solution
//--------------------------------------------------

/**
 * @brief Generate a new solution
 * @return Solution * Returns a Solution *
 */
Solution * GeneticOperations::Create()
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Breed a new solution
 * @param mother The mother solution that we are breeding from
 * @param father The father solution that we are breeding from
 * @return Solution * Returns a Solution *
 */
Solution * GeneticOperations::Breed(Solution * mother, Solution * father)
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Mutate a given solution
 * @param solution The solution that we are mutating
 * @return bool Returns a bool
 */
bool GeneticOperations::Mutate(Solution * solution)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Select Solution
//--------------------------------------------------

/**
 * @brief Select a solution from the population (using tournament select)
 * @param population The population that we are selecting from
 * @param tournamentSize The size of the tournament that we aer selecting for
 * @return Solution * Returns a Solution *
 */
Solution * GeneticOperations::Select(Population * population, int tournamentSize)
{
	throw runtime_error("Not implemented");
}
