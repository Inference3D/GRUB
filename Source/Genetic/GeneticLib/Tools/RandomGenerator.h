//--------------------------------------------------
// A random generator instance of the generator base
//
// @author: Wild Boar
//
// @date: 2023-06-05
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/RandomUtils.h>

namespace NVL_App
{
	class RandomGenerator
	{
	public:
		RandomGenerator() { NVLib::RandomUtils::TimeSeedRandomNumbers(); }
		virtual int Generate(int min, int max) override { return NVLib::RandomUtils::GetInteger(min, max);}
	};
}