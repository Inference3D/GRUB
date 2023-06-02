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
		double _score;
	public:
		Solution(int id, vector<int>& dna) : _id(id), _dna(dna) {}

		inline int& GetId() { return _id; }
		inline vector<int>& GetDna() { return _dna; }
		inline double& GetScore() { return _score; }

		inline void SetScore(double value) { _score = value; }
	};
}
