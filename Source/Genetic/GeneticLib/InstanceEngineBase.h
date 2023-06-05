//--------------------------------------------------
// A base class for representing the tangible elements of a solution
//
// @author: Wild Boar
//
// @date: 2023-06-05
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include "Solution.h"
#include "Tools/GeneratorBase.h"

namespace NVL_App
{
	class InstanceEngineBase
	{
	public:
		InstanceEngineBase() {}

		virtual Vec2d GetError(Solution * solution) = 0;
		virtual string ToString(Solution * solution) = 0;
		virtual Solution * Create(GeneratorBase * generator, int solutionId) = 0;
		virtual Solution * Breed(GeneratorBase * generator, int solutionId, Solution * mother, Solution * father) = 0;
		virtual bool Mutate(GeneratorBase * generator, Solution * solution, double probably) = 0;
	};
}
