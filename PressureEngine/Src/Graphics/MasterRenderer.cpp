#include "MasterRenderer.h"
#include "Water\WaterRenderer.h"
#include "Particles\ParticleMaster.h"

namespace Pressure {

	MasterRenderer::MasterRenderer(Window& window, Loader& loader, Camera& camera)
		: shader(), renderer(shader, window.getWindow()), skyboxRenderer(loader, window.getWindow()), shadowMapRenderer(camera, window), waterRenderer(window.getWindow(), waterBuffers), waterBuffers(window.getWindow()), entities() {
		enableCulling();
	}

	void MasterRenderer::render(std::vector<Light>& lights, Camera& camera) {
		prepare();
		shader.start();
		shader.connectTextureUnits();
		glDisable(GL_CLIP_DISTANCE0);
		shader.loadClipPlane(Vector4f(0, -1, 0, 1000000)); // Bit of a hack, as some drivers do not support disabling clip distance.
		shader.loadLights(lights);
		shader.loadViewMatrix(camera);
		renderer.render(entities, shadowMapRenderer.getToShadowMapSpaceMatrix());
		shader.stop();
		skyboxRenderer.render(camera);
		if (water.size() > 0) {
			renderWaterFrameBuffers(lights, camera);
			waterRenderer.render(water, lights, camera);
		}
		ParticleMaster::renderParticles(camera);
		entities.clear();
		water.clear();
	}

	void MasterRenderer::tick() {
		waterRenderer.tick();
	}

	void MasterRenderer::renderShadowMap(Light& sun) {
		shadowMapRenderer.render(entities, sun);
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

	unsigned int MasterRenderer::getShadowMapTexture() {
		return shadowMapRenderer.getShadowMap();
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
		//glClearColor(0.5, 0.5, 0.5, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, shadowMapRenderer.getShadowMap());
	}

	void MasterRenderer::renderWaterFrameBuffers(std::vector<Light>& lights, Camera& camera) {
		// Reflection rendering.
		waterBuffers.bindReflectionFrameBuffer();
		float distance = 2 * (camera.getPosition().getY() - water[0].getPosition().getY()); // Set up checking for which water is in frame.
		camera.getPosition().y -= distance;
		camera.invertPitch();
		prepare();
		shader.start();
		shader.connectTextureUnits();
		shader.loadClipPlane(Vector4f(0, 1, 0, -water[0].getPosition().getY() + 0.1f)); 
		shader.loadLights(lights);
		shader.loadViewMatrix(camera);
		renderer.render(entities, shadowMapRenderer.getToShadowMapSpaceMatrix());
		shader.stop();
		skyboxRenderer.render(camera);
		ParticleMaster::renderParticles(camera); // Refractionrendering too, clipplane?
		camera.getPosition().y += distance;
		camera.invertPitch();

		// Refraction rendering.
		waterBuffers.bindRefractionFrameBuffer();
		prepare();
		shader.start();
		shader.connectTextureUnits();
		shader.loadClipPlane(Vector4f(0,-1, 0, water[0].getPosition().getY() + 0.2f));
		shader.loadLights(lights);
		shader.loadViewMatrix(camera);
		renderer.render(entities, shadowMapRenderer.getToShadowMapSpaceMatrix());
		shader.stop();
		skyboxRenderer.render(camera);

		waterBuffers.unbindFrameBuffer();
	}

}