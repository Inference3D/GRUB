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

#include "Tools/GeneratorBase.h"
#include "Tools/ImageLoader.h"
#include "InstanceEngineBase.h"
#include "Solution.h"

namespace NVL_App
{
	class ImageClassifier : public InstanceEngineBase
	{
		private:
			ImageLoader * _loader;
		public:
			ImageClassifier(ImageLoader * loader);

			virtual Vec2d GetError(Solution * solution) override;
			virtual string ToString(Solution * solution) override;
			virtual Solution * Create(GeneratorBase * generator) override;
			virtual void Mutate(GeneratorBase * generator, Solution * solution, double probably) override;
	};
}
