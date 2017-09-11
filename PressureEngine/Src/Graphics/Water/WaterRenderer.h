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

	public:
		WaterRenderer(GLFWwindow* window);
		void updateProjectionmatrix();

		void render(std::vector<Water>& water, Camera& camera);

	};

}
