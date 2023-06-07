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
	_generator = new RandomGenerator();
	_operations = new GeneticOperations(_engine, _generator);
}

/**
 * @brief Main Terminator
 */
GeneticEngine::~GeneticEngine()
{
	if (_population != nullptr) delete _population;
	delete _operations;
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
		auto solution = _operations->Create();
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
 * @brief Add the logic to spawn the next generation
 */
void GeneticEngine::SpawnNew()
{
	// Create the next population
	auto nextPopulation = new Population();

	// Add the elitism variables
	auto topSolutions = vector<Solution *>(); _population->GetTopSolutions(_parameters->GetEliteCount(), topSolutions);
	for (auto solution : topSolutions) nextPopulation->AddSolution(new Solution(solution));

	// Use breeding to add the remainder of solutions 
	while (nextPopulation->GetSolutionCount() < _parameters->GetPopulationSize()) 
	{
		auto mother = _operations->Select(_population, _parameters->GetTournamentSize());
		auto father = _operations->Select(_population, _parameters->GetTournamentSize());
		auto child = _operations->Breed(mother, father);
		_operations->Mutate(child, _parameters->GetMutationProbability());
		nextPopulation->AddSolution(child);
	}

	// Swap the populations
	delete _population; _population = nextPopulation;
}
