#pragma once
#include <map>
#include <vector>

#include "Shaders\StaticShader.h"
#include "Models\TexturedModel.h"
#include "Renderer.h"
#include "Entities\Entity.h"
#include "Entities\Light.h"
#include "Entities\Camera.h"

namespace Pressure {

	class MasterRenderer {

	private: 
		StaticShader shader;
		Renderer renderer;

		std::map<TexturedModel, std::vector<Entity>> entities;

	public:
		MasterRenderer(GLFWwindow* window);
		void render(Light& light, Camera& camera);

		void processEntity(Entity& entity);
		void updateProjectionMatrix();

		static void enableCulling();
		static void disableCulling();

		Renderer& getRenderer();
		void cleanUp();

	};

}
