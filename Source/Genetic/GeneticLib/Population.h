//--------------------------------------------------
// A population that we are testing
//
// @author: Wild Boar
//
// @date: 2023-06-03
//--------------------------------------------------

#pragma once

#include <vector>
#include <iostream>
using namespace std;

#include "Solution.h"

namespace NVL_App
{
	class Population
	{
	private:
		vector<Solution *> _solutions;
	public:
		Population();
		~Population();

		void AddSolution(Solution * solution);
		int GetSolutionCount();
		void GetTopSolutions(int number, vector<Solution *>& result);

		inline vector<Solution *>& GetSolutions() { return _solutions; }
	};
}
