//--------------------------------------------------
// Implementation of class GeneticEngine
//
// @author: Wild Boar
//
// @date: 2023-06-06
//--------------------------------------------------

#include "GeneticEngine.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param parameters The parameters that we dealing with
 * @param engine The engine that we using to evaluate solutions
 */
GeneticEngine::GeneticEngine(GeneticParameters * parameters, InstanceEngineBase * engine) : _parameters(parameters), _engine(engine), _population(nullptr)
{
	_indexer = new Indexer();
	_generator = new RandomGenerator();
}

/**
 * @brief Main Terminator
 */
GeneticEngine::~GeneticEngine()
{
	if (_population != nullptr) delete _population;
	delete _indexer;
	delete _generator;
}

//--------------------------------------------------
// Initialize
//--------------------------------------------------

/**
 * @brief Generate the initial population of solutions
 */
void GeneticEngine::Initialize()
{
	// Make sure that the population is NULL
	if (_population != nullptr) delete _population;
	_population = nullptr;
	
	// Create a new population
	_population = new Population();

	// Create the associated solutions
	for (auto i = 0; i < _parameters->GetPopulationSize(); i++) 
	{
		auto solutionId = _indexer->Next();
		auto solution = _engine->Create(_generator, solutionId);
		_population->AddSolution(solution);
	}
}

//--------------------------------------------------
// Refinement
//--------------------------------------------------

/**
 * @brief Create the logic to evaluate solutions
 * @return The best solution so far
 */
Solution * GeneticEngine::EvaluateSolutions() 
{
	Solution * bestSolution = nullptr;

	for (auto solution : _population->GetSolutions()) 
	{
		auto error = _engine->GetError(solution);
		solution->SetError(error[_parameters->GetErrorType()]);

		if (bestSolution == nullptr) bestSolution = solution;
		else if (solution->GetError() < bestSolution->GetError()) bestSolution = solution;
	}

	return bestSolution;
}


/**
 * @brief Add refinement logic to the system
 * @return Solution * Returns a Solution *
 */
Solution * GeneticEngine::Refine()
{
	throw runtime_error("Not implemented");
}
