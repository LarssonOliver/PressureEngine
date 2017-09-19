#include "ParticleRenderer.h"

namespace Pressure {

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
		modelMatrix.setColumn(0, Vector4f(viewMatrix.get(0, 0), viewMatrix.get(1, 0), viewMatrix.get(2, 0), modelMatrix.get(0, 3)));
		modelMatrix.setColumn(1, Vector4f(viewMatrix.get(0, 1), viewMatrix.get(1, 1), viewMatrix.get(2, 1), modelMatrix.get(1, 3)));
		modelMatrix.setColumn(2, Vector4f(viewMatrix.get(0, 2), viewMatrix.get(1, 2), viewMatrix.get(2, 2), modelMatrix.get(2, 3)));
		modelMatrix.rotate(Math::toRadians(rotation), Vector3f(0, 0, 1));
		modelMatrix.scale(scale);
		modelMatrix.mul(viewMatrix);
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
