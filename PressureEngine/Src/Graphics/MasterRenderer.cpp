#include "MasterRenderer.h"

namespace Pressure {

	MasterRenderer::MasterRenderer(GLFWwindow* window)
		: shader(), renderer(shader, window), entities()
	{ }

	void MasterRenderer::render(Light& light, Camera& camera) {
		renderer.prepare();
		shader.start();
		shader.loadLight(light);
		shader.loadViewMatrix(camera);
		renderer.render(entities);
		shader.stop();
		entities.clear();
	}

	void MasterRenderer::processEntity(Entity& entity) {
		TexturedModel& entityModel = entity.getTexturedModel();
		std::vector<Entity>& batch = entities[entityModel];
		batch.emplace_back(entity);
	}

	void MasterRenderer::updateProjectionMatrix() {
		renderer.updateProjectionMatrix(shader);
	}

	Renderer& MasterRenderer::getRenderer() {
		return renderer;
	}

	void MasterRenderer::cleanUp() {
		shader.cleanUp();
	}

}