//--------------------------------------------------
// The parameters that we are dealing with
//
// @author: Wild Boar
//
// @date: 2023-06-02
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

namespace NVL_App
{
	class GeneticParameters
	{
	private:
		int _populationSize;
		int _tournamentSize;
		double _mutationProbability;
		int _eliteCount;
		int _errorType;
		int _maxIterations;
	public:
		GeneticParameters(int populationSize, int tournamentSize, double mutationProbability, int eliteCount, int errorType, int maxIterations) :
			_populationSize(populationSize), _tournamentSize(tournamentSize), _mutationProbability(mutationProbability), _eliteCount(eliteCount), _errorType(errorType), _maxIterations(maxIterations) {}

		inline int& GetPopulationSize() { return _populationSize; }
		inline int& GetTournamentSize() { return _tournamentSize; }
		inline double& GetMutationProbability() { return _mutationProbability; }
		inline int& GetEliteCount() { return _eliteCount; }
		inline int& GetErrorType() { return _errorType; }
		inline int& GetMaxIterations() { return _maxIterations; }
	};
}