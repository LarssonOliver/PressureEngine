#pragma once
#include <vector>
#include "../Models/RawModel.h"
#include "WaterShader.h"
#include "Water.h"
#include "WaterFrameBuffers.h"

namespace Pressure {

	class WaterRenderer {

	private:
		WaterShader shader;
		GLFWwindow* window;
		float waveModifier;

		WaterFrameBuffers& fbos;

	public:
		WaterRenderer(GLFWwindow* window, WaterFrameBuffers& fbos);
		void updateProjectionmatrix();

		// Used to time the waves.
		void tick();
		void render(std::vector<Water>& water, Light& sun, Camera& camera);

	};

}
