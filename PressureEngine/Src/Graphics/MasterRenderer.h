#pragma once
#include <map>
#include <vector>

#include "Shaders\EntityShader.h"
#include "Models\TexturedModel.h"
#include "Shaders\Renderer.h"
#include "Entities\Entity.h"
#include "Entities\Light.h"
#include "Entities\Camera.h"
#include "Skybox\SkyboxRenderer.h"
#include "Loader.h"
#include "Water\WaterRenderer.h"


namespace Pressure {

	class MasterRenderer {

	private: 
		EntityShader shader;
		Renderer renderer;

		SkyboxRenderer skyboxRenderer;
		WaterRenderer waterRenderer;

		std::map<TexturedModel, std::vector<Entity>> entities;
		std::vector<Water> water;

	public:
		MasterRenderer(GLFWwindow* window, Loader& loader);
		void render(Light& light, Camera& camera);

		void processEntity(Entity& entity);
		void processWater(Water& water);
		void updateProjectionMatrix();

		static void enableCulling();
		static void disableCulling();

		Renderer& getRenderer();
		void cleanUp();

	private:
		void prepare();

	};

}
