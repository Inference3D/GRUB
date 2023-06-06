//--------------------------------------------------
// The operations that we will use for genetic programming
//
// @author: Wild Boar
//
// @date: 2023-06-06
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include "Tools/GeneratorBase.h"
#include "InstanceEngineBase.h"
#include "Population.h"

namespace NVL_App
{
	class GeneticOperations
	{
	private:
		InstanceEngineBase * _engine;
		GeneratorBase * _generator;
	public:
		GeneticOperations(InstanceEngineBase * engine, GeneratorBase * generator);

		Solution * Create();
		Solution * Breed(Solution * mother, Solution * father);
		bool Mutate(Solution * solution);

		Solution * Select(Population * population, int tournamentSize);
	};
}
