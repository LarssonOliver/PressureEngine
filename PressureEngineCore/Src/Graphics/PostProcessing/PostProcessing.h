#pragma once

#include <vector>
#include "../Models/RawModel.h"
#include "../Loader.h"
#include "Contrast\ContrastChanger.h"
#include "LightScattering\LightScatterer.h"
#include "DepthOfField\DepthOfField.h"

namespace Pressure {

	class PostProcessing {
	
	private:
		static const std::vector<float> s_Positions;
		static std::unique_ptr<RawModel> s_Quad;
		static std::unique_ptr<ContrastChanger> s_ContrastChanger;
		static std::unique_ptr<LightScatterer> s_LightScatterer;
		static std::unique_ptr<DepthOfField> s_DepthOfField;
		static Window* s_Window;
		static Camera* s_Camera;
	
	public:
		static void init(Window& window, Camera& camera, Loader& loader);
		static void process(FrameBuffer& frameBuffer, unsigned int lightScatterTexture, Vector3f& lightPosition);
		static void updateProjectionMatrix();

	private:
		static void start();
		static void stop();

		PostProcessing() = delete;

	};

}