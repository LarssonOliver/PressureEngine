#include "MasterRenderer.h"

namespace Pressure {

	MasterRenderer::MasterRenderer(GLFWwindow* window, Loader& loader)
		: shader(), renderer(shader, window), skyboxRenderer(loader, window), waterRenderer(window), entities() {
		enableCulling();
	}

	void MasterRenderer::render(Light& light, Camera& camera) {
		prepare();
		shader.start();
		shader.loadLight(light);
		shader.loadViewMatrix(camera);
		renderer.render(entities);
		shader.stop();
		skyboxRenderer.render(camera);
		if (water.size() > 0)
			waterRenderer.render(water, camera);
		entities.clear();
		water.clear();
	}

	void MasterRenderer::processEntity(Entity& entity) {
		TexturedModel& entityModel = entity.getTexturedModel();
		std::vector<Entity>& batch = entities[entityModel];
		batch.emplace_back(entity);
	}

	void MasterRenderer::processWater(Water& water) {
		this->water.emplace_back(water);
	}

	void MasterRenderer::updateProjectionMatrix() {
		renderer.updateProjectionMatrix(shader);
		skyboxRenderer.updateProjectionMatrix();
		waterRenderer.updateProjectionmatrix();
	}

	void MasterRenderer::enableCulling() {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	void MasterRenderer::disableCulling() {
		glDisable(GL_CULL_FACE);
	}

	Renderer& MasterRenderer::getRenderer() {
		return renderer;
	}

	void MasterRenderer::cleanUp() {
		shader.cleanUp();
	}

	void MasterRenderer::prepare() {
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5, 0.5, 0.5, 1);
	}

}