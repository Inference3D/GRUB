//--------------------------------------------------
// A base class for unit tests that can swap between "real" and "unit test" versions
//
// @author: Wild Boar
//
// @date: 2023-06-05
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

namespace NVL_App
{
	class GeneratorBase
	{
	public:
		GeneratorBase() {}
		virtual int Generate(int min, int max) = 0;
	};
}
