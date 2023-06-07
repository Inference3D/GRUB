//--------------------------------------------------
// Implementation of class Classifier
//
// @author: Wild Boar
//
// @date: 2023-06-05
//--------------------------------------------------

#include "LearnWrapper.h"
using namespace NVL_AI;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param loader Defines an image loader for the system
 * @param kernelSize The size of the kernel that we are working with
 */
LearnWrapper::LearnWrapper(ImageLoader * loader, int kernelSize) : _loader(loader), _kernelSize(kernelSize)
{
	// Extra implementation can go here
}

//--------------------------------------------------
// Evaluation
//--------------------------------------------------

/**
 * @brief Retrieve the error for the given solution
 * @param solution The solution that we are testing
 * @return Vec2d Returns a Vec2d
 */
Vec2d LearnWrapper::GetError(Solution * solution)
{
	// Create the kernel
	auto kernel =  Kernel(solution);

	// Create a variable to determine score
	auto result = Vec2d();

	// Reset the loader
	_loader->Reset();

	while (true) 
	{
		// Retrieve the next test (if it exists)
		auto test = _loader->Next();
		if (test.get() == nullptr) break;

		// Perform the test
		auto score = kernel.Evaluate(test->GetImage());

		// Determine the classification and classification difference
		auto classification = score > 50 ? 0 : 1;
		auto counter = classification == test->GetImageType() ? 0 : 1;

		auto error = test->GetImageType() == 0 ? abs(100 - score) : abs(score + 100);

		// Perform the update
		result[0] += error; result[1] += counter;
	}

	// Return the result
	return result;
}

//--------------------------------------------------
// String Representation
//--------------------------------------------------

/**
 * @brief Retrieve a string representation
 * @param solution The solution that we are working with
 * @return string Returns a string
 */
string LearnWrapper::ToString(Solution * solution)
{
	return NVLib::Formatter() << "[kernel:" << solution->GetId() << "]";
}

//--------------------------------------------------
// Generate
//--------------------------------------------------

/**
 * @brief Generate new solutions
 * @param generator A source of random numbers
 * @param solutionId An identifier for the solution
 * @return Solution * Returns a Solution *
 */
Solution * LearnWrapper::Create(GeneratorBase * generator, int solutionId)
{
	// Create the "DNA" for the solution
	auto dna = vector<int>(); auto pixelCount = _kernelSize * _kernelSize; 
	for (auto i = 0; i < pixelCount; i++) dna.push_back(generator->Generate(-1000, 1000));

	// Add the scale factor
	dna.push_back(1e4);

	// Add the offset
	dna.push_back(0 /*generator->Generate(-1000, 1000)*/ );

	// Return the solution
	return new Solution(solutionId, dna);
}

//--------------------------------------------------
// Breed
//--------------------------------------------------

/**
 * @brief Add associated breed logic
 * @param generator The generator that we are using
 * @param solutionId The identifier to be given to the child
 * @param mother The father node
 * @param father The mother node
 * @return Solution* The given solution
 */
Solution * LearnWrapper::Breed(GeneratorBase * generator, int solutionId, Solution * mother, Solution * father) 
{
	// Perform validations
	assert(mother->GetDna().size() > 0); // There needs to be some DNA entries in the data
	assert(mother->GetDna().size() == father->GetDna().size()); // The father and mother need to have the same set size

	// Create a variable to hold the child DNA
	auto dna = vector<int>();

	// Perform the population of the DNA
	for (auto i = 0; i < mother->GetDna().size(); i++) 
	{
		auto selection = generator->Generate(0, 2);
		auto value = selection == 0 ? mother->GetDna()[i] : father->GetDna()[i];
		dna.push_back(value);
	}

	// Return the new solution
	return new Solution(solutionId, dna);
}

//--------------------------------------------------
// Mutate
//--------------------------------------------------

/**
 * @brief Mutate solutions
 * @param generator A source of random numbers
 * @param solution The solution that is potentially mutate
 * @param probability The probability that the solution will be mutated
 * @return An indication whether the solution was mutated or not
 */
bool LearnWrapper::Mutate(GeneratorBase * generator, Solution * solution, double probability)
{
	// Determine if a mutation should occur?
	auto spin = generator->Generate(0, 100);
	auto threshold = 100 * probability;
	if (spin > threshold) return false;

	// Select the attribute to change
	auto attributeIndex = generator->Generate(0, solution->GetDna().size() - 1);

	// Get the new attribute value
	auto value = generator->Generate(-1000, 1000);

	// Perform the update
	solution->GetDna()[attributeIndex] = value;

	// Mutation was successfully performed
	return true;
}