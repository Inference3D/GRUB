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
	_indexer = new Indexer();
}

/**
 * @brief Main Terminator
 */
GeneticOperations::~GeneticOperations() 
{
	delete _indexer;
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
	auto solutionId = _indexer->Next();
	return _engine->Create(_generator, solutionId);
}

/**
 * @brief Breed a new solution
 * @param mother The mother solution that we are breeding from
 * @param father The father solution that we are breeding from
 * @return Solution * Returns a Solution *
 */
Solution * GeneticOperations::Breed(Solution * mother, Solution * father)
{
	auto solutionId = _indexer->Next();
	return _engine->Breed(_generator, solutionId, mother, father);
}

/**
 * @brief Mutate a given solution
 * @param solution The solution that we are mutating
 * @param probability The probability that a mutation will occur
 * @return bool Returns a bool
 */
bool GeneticOperations::Mutate(Solution * solution, double probability)
{
	return _engine->Mutate(_generator, solution, probability);
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
	// Generate the first index
	auto index = _generator->Generate(0, population->GetSolutionCount());

	// Create a variable to hold the result
	auto result = population->GetSolutions()[index];

	// Try out some other options
	for (auto i = 0; i < tournamentSize - 1; i++) 
	{
		index = _generator->Generate(0, population->GetSolutionCount());
		auto option = population->GetSolutions()[index];
		if (option->GetError() < result->GetError()) result = option;
	}

	// Return the result that was found
	return result;
}
