#include "ParticleRenderer.h"

namespace Pressure {

	const std::vector<float> ParticleRenderer::VERTICES = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };

	ParticleRenderer::ParticleRenderer(Loader& loader, Matrix4f& projectionMatrix)
		: quad(loader.loadToVao(VERTICES, 2)) {
		shader.start();
		shader.loadProjectionMatrix(projectionMatrix);
	}

	void ParticleRenderer::render(std::list<Particle>& particles, Camera& camera) {
		Matrix4f viewMatrix;
		viewMatrix.createViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw(), camera.getRoll());
		prepare();
		for (Particle& particle : particles) {
			updateViewMatrix(particle.getPosition(), particle.getRotation(), particle.getScale(), viewMatrix);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, quad->getVertexCount());
		}
		finish();
	}

	void ParticleRenderer::cleanUp() {
		shader.cleanUp();
	}

	void ParticleRenderer::prepare() {
		shader.start();
		quad->getVao()->bind();
		glEnableVertexAttribArray(0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(false);
	}

	void ParticleRenderer::updateViewMatrix(Vector3f& position, float rotation, float scale, Matrix4f& viewMatrix) {
		Matrix4f modelMatrix;
		modelMatrix.translate(position);
		modelMatrix.rotate(Math::toRadians(rotation), Vector3f(0, 0, 1));
		modelMatrix.scale(scale);
		modelMatrix.mul(viewMatrix);
		modelMatrix.set(0, 0, 1);
		modelMatrix.set(0, 1, 0);
		modelMatrix.set(0, 2, 0);
		modelMatrix.set(1, 0, 0);
		modelMatrix.set(1, 1, 1);
		modelMatrix.set(1, 2, 0);
		modelMatrix.set(2, 0, 0);
		modelMatrix.set(2, 1, 0);
		modelMatrix.set(2, 2, 1);
		shader.loadViewMatrix(modelMatrix);
	}

	void ParticleRenderer::finish() {
		glDepthMask(true);
		glDisable(GL_BLEND);
		glDisableVertexAttribArray(0);
		glBindVertexArray(NULL);
		shader.stop();
	}

}
