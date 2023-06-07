//--------------------------------------------------
// A solution in the genetic context
//
// @author: Wild Boar
//
// @date: 2023-06-02
//--------------------------------------------------

#pragma once

#include <vector>
#include <iostream>
using namespace std;

namespace NVL_App
{
	class Solution
	{
	private:
		int _id;
		vector<int> _dna;
		double _error;
	public:
		Solution(int id, const vector<int>& dna) : _id(id), _dna(dna), _error(-1) {}
		Solution(Solution * solution) : _id(solution->_id), _dna(solution->GetDna()), _error(solution->GetError()) {}

		inline int& GetId() { return _id; }
		inline vector<int>& GetDna() { return _dna; }
		inline double& GetError() { return _error; }

		inline void SetError(double value) { _error = value; }
	};
}
