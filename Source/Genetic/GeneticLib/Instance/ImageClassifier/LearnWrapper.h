//--------------------------------------------------
// An instance of an image classifier
//
// @author: Wild Boar
//
// @date: 2023-06-05
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include <NVLib/Formatter.h>

#include "Tools/GeneratorBase.h"
#include "Tools/ImageLoader.h"
#include "InstanceEngineBase.h"
#include "Solution.h"
using namespace NVL_App;

#include "Kernel.h"

namespace NVL_AI
{
	class LearnWrapper : public InstanceEngineBase
	{
	private:
		ImageLoader * _loader;
		int _kernelSize;
	public:
		LearnWrapper(ImageLoader * loader, int kernelSize = 100);

		virtual Vec2d GetError(Solution * solution) override;
		virtual string ToString(Solution * solution) override;
		virtual Solution * Create(GeneratorBase * generator, int solutionId) override;
		virtual Solution * Breed(GeneratorBase * generator, int solutionId, Solution * mother, Solution * father) override;
		virtual bool Mutate(GeneratorBase * generator, Solution * solution, double probably) override;
	};
}
