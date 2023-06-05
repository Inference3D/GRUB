//--------------------------------------------------
// A base class for representing the tangible elements of a solution
//
// @author: Wild Boar
//
// @date: 2023-06-05
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.h>

#include "Solution.h"

namespace NVL_App
{
	class InstanceEngineBase
	{
	public:
		InstanceEngineBase() {}

		virtual Vec2d GetError(Solution * solution) = 0;
		virtual string ToString(Solution * solution) = 0;
		virtual Solution * Create() = 0;
		virtual void Mutate(Solution * solution, double probably) = 0;
	};
}
