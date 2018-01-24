#pragma once
#include <vector>
#include "SkyboxShader.h"
#include "../Loader.h"

namespace Pressure {

#define PRESSURE_SKYBOX_SIZE 500.f
#define PRESSURE_SKYBOX_FILE "skybox/skybox"

	class SkyboxRenderer {

	private:
		static const std::vector<float> VERTICES;

		RawModel cube;
		int texture;
		SkyboxShader shader;
		GLFWwindow* const window;

	public:
		SkyboxRenderer(Loader& loader, GLFWwindow* window);
		void updateProjectionMatrix();

		void render(Camera& camera);

	};

}
