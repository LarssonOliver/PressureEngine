#pragma once

#include <vector>
#include "../Models/RawModel.h"
#include "../Loader.h"
#include "Contrast\ContrastChanger.h"

namespace Pressure {

	class PostProcessing {
	
	private:
		static const std::vector<float> s_Positions;
		static std::unique_ptr<RawModel> s_Quad;
		static std::unique_ptr<ContrastChanger> s_ContrastChanger;
	
	public:
		static void init(Loader& loader);
		static void process(unsigned int colorTexture);

	private:
		static void start();
		static void stop();

		PostProcessing() = delete;

	};

}