#pragma once

#include <vector>
#include "../Models/RawModel.h"
#include "../Loader.h"
#include "Contrast\ContrastChanger.h"
#include "LightScattering\LightScatterer.h"

namespace Pressure {

	class PostProcessing {
	
	private:
		static const std::vector<float> s_Positions;
		static std::unique_ptr<RawModel> s_Quad;
		static std::unique_ptr<ContrastChanger> s_ContrastChanger;
		static std::unique_ptr<LightScatterer> s_LightScatterer;
		static Window* s_Window;
	
	public:
		static void init(Window& window, Loader& loader);
		static void process(unsigned int colorTexture, unsigned int lightScatterTexture);

	private:
		static void start();
		static void stop();

		PostProcessing() = delete;

	};

}