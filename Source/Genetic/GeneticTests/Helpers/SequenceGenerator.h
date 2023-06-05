//--------------------------------------------------
// Defines a generator that "recalls" a sequence
//
// @author: Wild Boar
//
// @date: 2023-06-05
//--------------------------------------------------

#pragma once

#include <vector>
#include <iostream>
using namespace std;

#include <GeneticLib/Tools/GeneratorBase.h>

namespace NVL_App
{
	class SequenceGenerator : public GeneratorBase
	{
	private:
		vector<int> _values;
		int _position;
	public:
		SequenceGenerator(const vector<int>& values) : _values(values), _position(0) {}

		/**
		 * @brief Retrieve elements in the sequence and throw errors if constraints are violated
		 * @param min The minimum value that we are allowed
		 * @param max  The maximum value that we are allowed
		 * @return int The generated value
		 */
		virtual int Generate(int min, int max) override 
		{
			if (_position >= _values.size()) throw runtime_error("Sequence Generator ran out of expected tokens");
			auto value = _values[_position++];
			if (value < min || value > max) throw runtime_error("Generated token appears to be out of range!");
			return value;
		}

	};
}
