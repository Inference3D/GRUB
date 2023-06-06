//--------------------------------------------------
// An engine for performing genetic programming
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

#include "Tools/Indexer.h"
#include "Tools/RandomGenerator.h"

#include "GeneticOperations.h"
#include "GeneticParameters.h"
#include "Population.h"

namespace NVL_App
{
	class GeneticEngine
	{
	private:
		Population * _population;
		GeneticParameters * _parameters;
		InstanceEngineBase * _engine;
		Indexer * _indexer;
		GeneratorBase * _generator;
	public:
		GeneticEngine(GeneticParameters * parameters, InstanceEngineBase * engine);
		~GeneticEngine();

		void Initialize();
		Solution * EvaluateSolutions();
		Solution * Refine();

		inline Population * GetPopulation() { return _population; }
	};
}
