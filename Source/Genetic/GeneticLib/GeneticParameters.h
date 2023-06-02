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
	public:
		GeneticParameters(int populationSize, int tournamentSize, double mutationProbability, int eliteCount) :
			_populationSize(populationSize), _tournamentSize(tournamentSize), _mutationProbability(mutationProbability), _eliteCount(eliteCount) {}

		inline int& GetPopulationSize() { return _populationSize; }
		inline int& GetTournamentSize() { return _tournamentSize; }
		inline double& GetMutationProbability() { return _mutationProbability; }
		inline int& GetEliteCount() { return _eliteCount; }
	};
}