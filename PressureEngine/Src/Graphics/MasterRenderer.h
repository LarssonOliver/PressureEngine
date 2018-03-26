#pragma once
#include <unordered_map>
#include <vector>

#include "EntityShaders\EntityShader.h"
#include "Models\TexturedModel.h"
#include "EntityShaders\EntityRenderer.h"
#include "Entities\Entity.h"
#include "Entities\Light.h"
#include "Entities\Camera.h"
#include "Skybox\SkyboxRenderer.h"
#include "Loader.h"
#include "Water\WaterRenderer.h"
#include "GLObjects\FrameBuffer.h"
#include "Shadows\ShadowMapMasterRenderer.h"

namespace Pressure {

	class MasterRenderer {

	private: 
		EntityShader shader;
		EntityRenderer renderer;

		SkyboxRenderer skyboxRenderer;
		ShadowMapMasterRenderer shadowMapRenderer;
		
		WaterRenderer waterRenderer;

		std::unordered_map<TexturedModel, std::vector<Entity>> entities;
		std::vector<Water> water;

	public:
		MasterRenderer(Window& window, Loader& loader, Camera& camera);
		void render(std::vector<Light>& lights, Camera& camera);
		void tick();
		
		// IMPORTANT! Has to be called before render();
		void renderShadowMap(Light& sun);
		void renderWaterFrameBuffers(std::vector<Light>& lights, Camera& camera);

		void processEntity(Entity& entity);
		void processWater(Water& water);
		void updateProjectionMatrix();

		static void enableCulling();
		static void enableFrontFaceCulling();
		static void disableCulling();

		//for debugging.
		unsigned int getShadowMapTexture();

		EntityRenderer& getRenderer();
		void cleanUp();

	private:
		void prepare();

	};

}
