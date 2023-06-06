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
#include "Tools/Indexer.h"

#include "InstanceEngineBase.h"
#include "Population.h"

namespace NVL_App
{
	class GeneticOperations
	{
	private:
		InstanceEngineBase * _engine;
		GeneratorBase * _generator;
		Indexer * _indexer;
	public:
		GeneticOperations(InstanceEngineBase * engine, GeneratorBase * generator);
		virtual ~GeneticOperations();

		Solution * Create();
		Solution * Breed(Solution * mother, Solution * father);
		bool Mutate(Solution * solution, double probability);

		Solution * Select(Population * population, int tournamentSize);
	};
}
