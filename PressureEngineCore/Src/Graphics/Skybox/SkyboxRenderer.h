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

		RawModel m_Cube;
		int m_Texture;
		SkyboxShader m_Shader;
		GLFWwindow* const m_Window;

	public:
		SkyboxRenderer(Loader& loader, GLFWwindow* window);
		void updateProjectionMatrix();

		void render(Camera& camera);

	};

}
