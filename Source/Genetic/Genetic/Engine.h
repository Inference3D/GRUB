//--------------------------------------------------
// Defines a basic engine for a vanilla C++ project.
//
// @author: Wild Boar
//
// @date: 2023-06-02
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/Logger.h>
#include <NVLib/DisplayUtils.h>
#include <NVLib/Graphics/Graph.h>

#include <GeneticLib/ArgUtils.h>
#include <GeneticLib/GeneticParameters.h>
#include <GeneticLib/Tools/ImageLoader.h>
#include <GeneticLib/GeneticEngine.h>
#include <GeneticLib/Instance/ImageClassifier/LearnWrapper.h>

namespace NVL_App
{
	class Engine
	{
	private:
		NVLib::Parameters * _parameters;
		NVLib::Logger* _logger;
		ImageLoader * _loader;
		GeneticParameters * _learningArguments;
		NVL_AI::LearnWrapper * _learningWrapper;
		GeneticEngine * _learner;
	public:
		Engine(NVLib::Logger* logger, NVLib::Parameters * parameters);
		~Engine();

		void Run();
	};
}
