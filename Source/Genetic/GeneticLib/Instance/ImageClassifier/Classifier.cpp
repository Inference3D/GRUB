//--------------------------------------------------
// Implementation of class Classifier
//
// @author: Wild Boar
//
// @date: 2023-06-05
//--------------------------------------------------

#include "Classifier.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param loader Defines an image loader for the system
 */
Classifier::Classifier(ImageLoader * loader)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Evaluation
//--------------------------------------------------

/**
 * @brief Retrieve the error for the given solution
 * @param solution The solution that we are testing
 * @return Vec2d Returns a Vec2d
 */
Vec2d Classifier::GetError(Solution * solution)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// String Representation
//--------------------------------------------------

/**
 * @brief Retrieve a string representation
 * @param  
 * @return string Returns a string
 */
string Classifier::ToString(Solution * )
{
	throw runtime_error("Not implemented");
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
Solution * Classifier::Create(GeneratorBase * generator, int solutionId)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Mutate
//--------------------------------------------------

/**
 * @brief Mutate solutions
 * @param generator A source of random numbers
 * @param solution The solution that is potentially mutate
 * @param probably The probably that the solution will be mutated
 * @return An indication whether the solution was mutated or not
 */
bool Classifier::Mutate(GeneratorBase * generator, Solution * solution, double probably)
{
	throw runtime_error("Not implemented");
}
