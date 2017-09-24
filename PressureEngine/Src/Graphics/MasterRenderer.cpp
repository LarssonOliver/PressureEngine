#include "MasterRenderer.h"

namespace Pressure {

	MasterRenderer::MasterRenderer(GLFWwindow* window, Loader& loader)
		: shader(), renderer(shader, window), skyboxRenderer(loader, window), waterRenderer(window, waterBuffers), waterBuffers(window), entities() {
		enableCulling();
	}

	void MasterRenderer::render(Light& light, Camera& camera) {
		prepare();
		shader.start();
		glDisable(GL_CLIP_DISTANCE0);
		shader.loadClipPlane(Vector4f(0, -1, 0, 1000000)); // Bit of a hack, as some drivers do not support disabling clip distance.
		shader.loadLight(light);
		shader.loadViewMatrix(camera);
		renderer.render(entities);
		shader.stop();
		skyboxRenderer.render(camera);
		if (water.size() > 0) {
			renderWaterFrameBuffers(light, camera);
			waterRenderer.render(water, light, camera);
		}
		entities.clear();
		water.clear();
	}

	void MasterRenderer::tick() {
		waterRenderer.tick();
	}

	void MasterRenderer::processEntity(Entity& entity) {
		TexturedModel& entityModel = entity.getTexturedModel();
		std::vector<Entity>& batch = entities[entityModel];
		batch.push_back(entity);
	}

	void MasterRenderer::processWater(Water& water) {
		this->water.push_back(water);
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
		glEnable(GL_CLIP_DISTANCE0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5, 0.5, 0.5, 1);
	}

	void MasterRenderer::renderWaterFrameBuffers(Light& light, Camera& camera) {
		// Reflection rendering.
		waterBuffers.bindReflectionFrameBuffer();
		float distance = 2 * (camera.getPosition().getY() - water[0].getPosition().getY()); // Set up checking for which water is in frame.
		camera.getPosition().y -= distance;
		camera.invertPitch();
		prepare();
		shader.start();
		shader.loadClipPlane(Vector4f(0, 1, 0, -water[0].getPosition().getY() + 0.5)); 
		shader.loadLight(light);
		shader.loadViewMatrix(camera);
		renderer.render(entities);
		shader.stop();
		skyboxRenderer.render(camera);
		camera.getPosition().y += distance;
		camera.invertPitch();

		// Refraction rendering.
		waterBuffers.bindRefractionFrameBuffer();
		prepare();
		shader.start();
		shader.loadClipPlane(Vector4f(0, -1, 0, water[0].getPosition().getY() + 0.2));
		shader.loadLight(light);
		shader.loadViewMatrix(camera);
		renderer.render(entities);
		shader.stop();
		skyboxRenderer.render(camera);

		waterBuffers.unbindFrameBuffer();
	}

}