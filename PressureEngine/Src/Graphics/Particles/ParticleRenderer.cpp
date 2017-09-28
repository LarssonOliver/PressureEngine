#include "ParticleRenderer.h"
#include "../Textures/TextureManager.h"

namespace Pressure {

	const std::vector<float> ParticleRenderer::VERTICES = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };
	const int ParticleRenderer::MAX_INSTANCES = 10000;
	const int ParticleRenderer::INSTANCE_DATA_LENGTH = 21;

	std::vector<float> ParticleRenderer::buffer;

	ParticleRenderer::ParticleRenderer(Loader& loader, Matrix4f& projectionMatrix)
		: quad(loader.loadToVao(VERTICES, 2)), loader(loader), vbo(loader.createEmptyVbo(INSTANCE_DATA_LENGTH)) {
		loader.addInstancedAttribute(quad->getVaoID(), vbo, 1, 4, INSTANCE_DATA_LENGTH, 0);
		loader.addInstancedAttribute(quad->getVaoID(), vbo, 2, 4, INSTANCE_DATA_LENGTH, 4);
		loader.addInstancedAttribute(quad->getVaoID(), vbo, 3, 4, INSTANCE_DATA_LENGTH, 8);
		loader.addInstancedAttribute(quad->getVaoID(), vbo, 4, 4, INSTANCE_DATA_LENGTH, 12);
		loader.addInstancedAttribute(quad->getVaoID(), vbo, 5, 4, INSTANCE_DATA_LENGTH, 16);
		loader.addInstancedAttribute(quad->getVaoID(), vbo, 6, 1, INSTANCE_DATA_LENGTH, 20);
		shader.start();
		shader.loadProjectionMatrix(projectionMatrix);
	}

	void ParticleRenderer::render(std::map<ParticleTexture, std::list<Particle>>& particles, Camera& camera) {
		Matrix4f viewMatrix;
		viewMatrix.createViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw(), camera.getRoll());
		prepare();

		for (auto it = particles.begin(); it != particles.end(); it++) {
			bindTexture(it->first);
			pointer = 0;
			this->buffer = std::vector<float>(it->second.size() * INSTANCE_DATA_LENGTH);
			for (Particle& particle : it->second) {
				updateViewMatrix(particle.getPosition(), particle.getRotation(), particle.getScale(), viewMatrix);
				updateTexCoordInfo(particle);
			}
			loader.updateVbo(vbo, buffer);
			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, quad->getVertexCount(), it->second.size());
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
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		glEnableVertexAttribArray(5);
		glEnableVertexAttribArray(6);
		glEnable(GL_BLEND);
		glDepthMask(false);
	}

	void ParticleRenderer::bindTexture(const ParticleTexture& texture) {
		glActiveTexture(GL_TEXTURE0);
		if (texture.isUseAdditiveBlending())
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		else 
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		TextureManager::Inst()->BindTexture(texture.getTextureID());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		shader.loadNumberOfRows(texture.getNumberOfRows());
	}

	void ParticleRenderer::updateViewMatrix(Vector3f& position, float rotation, float scale, Matrix4f& viewMatrix) {
		Matrix4f modelMatrix;
		modelMatrix.translate(position);
		modelMatrix.rotate((float) Math::toRadians(rotation), Vector3f(0, 0, 1));
		modelMatrix.scale(scale);
		viewMatrix.mul(modelMatrix, modelMatrix);
		modelMatrix.set(0, 0, 1);
		modelMatrix.set(0, 1, 0);
		modelMatrix.set(0, 2, 0);
		modelMatrix.set(1, 0, 0);
		modelMatrix.set(1, 1, 1);
		modelMatrix.set(1, 2, 0);
		modelMatrix.set(2, 0, 0);
		modelMatrix.set(2, 1, 0);
		modelMatrix.set(2, 2, 1);
		storeMatrixData(modelMatrix);
	}

	void ParticleRenderer::storeMatrixData(Matrix4f& matrix) {
		buffer[pointer++] = matrix.get(0, 0);
		buffer[pointer++] = matrix.get(0, 1);
		buffer[pointer++] = matrix.get(0, 2);
		buffer[pointer++] = matrix.get(0, 3);
		buffer[pointer++] = matrix.get(1, 0);
		buffer[pointer++] = matrix.get(1, 1);
		buffer[pointer++] = matrix.get(1, 2);
		buffer[pointer++] = matrix.get(1, 3);
		buffer[pointer++] = matrix.get(2, 0);
		buffer[pointer++] = matrix.get(2, 1);
		buffer[pointer++] = matrix.get(2, 2);
		buffer[pointer++] = matrix.get(2, 3);
		buffer[pointer++] = matrix.get(3, 0);
		buffer[pointer++] = matrix.get(3, 1);
		buffer[pointer++] = matrix.get(3, 2);
		buffer[pointer++] = matrix.get(3, 3);
	}

	void ParticleRenderer::updateTexCoordInfo(Particle& particle) {
		buffer[pointer++] = particle.getCurrentUV().getX();
		buffer[pointer++] = particle.getCurrentUV().getY();
		buffer[pointer++] = particle.getBlendUV().getX();
		buffer[pointer++] = particle.getBlendUV().getY();
		buffer[pointer++] = particle.getBlend();
	}

	void ParticleRenderer::finish() {
		glDepthMask(true);
		glDisable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, NULL);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
		glDisableVertexAttribArray(5);
		glDisableVertexAttribArray(6);
		glBindVertexArray(NULL);
		shader.stop();
	}

}
