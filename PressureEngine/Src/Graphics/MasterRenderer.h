#pragma once
#include <map>
#include <vector>

#include "Shaders\StaticShader.h"
#include "Models\TexturedModel.h"
#include "Renderer.h"
#include "Entities\Entity.h"
#include "Entities\Light.h"
#include "Entities\Camera.h"
#include "Skybox\SkyboxRenderer.h"
#include "Loader.h"


namespace Pressure {

	class MasterRenderer {

	private: 
		StaticShader shader;
		Renderer renderer;

		SkyboxRenderer skyboxRenderer;

		std::map<TexturedModel, std::vector<Entity>> entities;

	public:
		MasterRenderer(GLFWwindow* window, Loader& loader);
		void render(Light& light, Camera& camera);

		void processEntity(Entity& entity);
		void updateProjectionMatrix();

		static void enableCulling();
		static void disableCulling();

		Renderer& getRenderer();
		void cleanUp();

	};

}
