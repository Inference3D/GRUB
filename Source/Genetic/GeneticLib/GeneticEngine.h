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
	public:
		GeneticEngine(GeneticParameters * parameters, InstanceEngineBase * engine);
		~GeneticEngine();

		void Initialize();
		Solution * Refine();

		inline Population * GetPopulation() { return _population; }
	};
}
