#pragma once
#include <vector>
#include "../Models/RawModel.h"
#include "WaterShader.h"
#include "Water.h"

namespace Pressure {

	class WaterRenderer {

	private:
		WaterShader shader;
		GLFWwindow* window;
		float waveModifier;

	public:
		WaterRenderer(GLFWwindow* window);
		void updateProjectionmatrix();

		// Used to time the waves.
		void tick();
		void render(std::vector<Water>& water, Camera& camera);

	};

}
