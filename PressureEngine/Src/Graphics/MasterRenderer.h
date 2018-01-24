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
#include "Water\WaterFrameBuffers.h"
#include "Shadows\ShadowMapMasterRenderer.h"

namespace Pressure {

	class MasterRenderer {

	private: 
		EntityShader shader;
		Renderer renderer;

		SkyboxRenderer skyboxRenderer;
		ShadowMapMasterRenderer shadowMapRenderer;
		
		WaterRenderer waterRenderer;
		WaterFrameBuffers waterBuffers;

		std::map<TexturedModel, std::vector<Entity>> entities;
		std::vector<Water> water;

	public:
		MasterRenderer(Window& window, Loader& loader, Camera& camera);
		void render(std::vector<Light>& lights, Camera& camera);
		void tick();
		
		// IMPORTANT! Has to be called before render();
		void renderShadowMap(Light& sun);

		void processEntity(Entity& entity);
		void processWater(Water& water);
		void updateProjectionMatrix();

		static void enableCulling();
		static void disableCulling();

		//for debugging.
		unsigned int getShadowMapTexture();

		Renderer& getRenderer();
		void cleanUp();

	private:
		void prepare();
		void renderWaterFrameBuffers(std::vector<Light>& lights, Camera& camera);

	};

}
