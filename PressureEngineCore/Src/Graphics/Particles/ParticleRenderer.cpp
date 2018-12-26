#include "ParticleRenderer.h"
#include "../Textures/TextureManager.h"

namespace Pressure {

	const std::vector<float> ParticleRenderer::VERTICES = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };
	const int ParticleRenderer::MAX_INSTANCES = 10000;
	const int ParticleRenderer::INSTANCE_DATA_LENGTH = 21;

	std::vector<float> ParticleRenderer::s_Buffer;

	ParticleRenderer::ParticleRenderer(Loader& loader, Matrix4f& projectionMatrix)
		: m_Quad(loader.loadToVao(VERTICES, 2)), m_vbo(nullptr, INSTANCE_DATA_LENGTH) {
		m_Quad.getVertexArray().bind();
		m_vbo.addInstancedAttribute(1, 4, INSTANCE_DATA_LENGTH, 0);
		m_vbo.addInstancedAttribute(2, 4, INSTANCE_DATA_LENGTH, 4);
		m_vbo.addInstancedAttribute(3, 4, INSTANCE_DATA_LENGTH, 8);
		m_vbo.addInstancedAttribute(4, 4, INSTANCE_DATA_LENGTH, 12);
		m_vbo.addInstancedAttribute(5, 4, INSTANCE_DATA_LENGTH, 16);
		m_vbo.addInstancedAttribute(6, 1, INSTANCE_DATA_LENGTH, 20);
		m_Quad.getVertexArray().unbind();
		m_Shader.start();
		m_Shader.loadProjectionMatrix(projectionMatrix);
	}

	void ParticleRenderer::render(std::map<ParticleTexture, std::list<Particle>>& particles, Camera& camera) {
		Matrix4f viewMatrix;
		viewMatrix.createViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw(), camera.getRoll());
		prepare();

		for (auto it = particles.begin(); it != particles.end(); it++) {
			bindTexture(it->first);
			m_Pointer = 0;
			this->s_Buffer = std::vector<float>(it->second.size() * INSTANCE_DATA_LENGTH);
			for (Particle& particle : it->second) {
				if (ViewFrustum::Inst().sphereInFrustum(particle.getPosition(), std::sqrtf(3.f) / 2 * particle.getScale())) {
					updateViewMatrix(particle.getPosition(), particle.getRotation(), particle.getScale(), viewMatrix);
					updateTexCoordInfo(particle);
				}
			}
			m_vbo.update(&s_Buffer[0], s_Buffer.size() * sizeof(float));
			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, m_Quad.getVertexCount(), it->second.size());
		}
		finish();
	}

	void ParticleRenderer::cleanUp() {
		m_Shader.cleanUp();
	}

	void ParticleRenderer::prepare() {
		m_Shader.start();
		m_Quad.getVertexArray().bind();
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		m_Shader.loadNumberOfRows((float) texture.getNumberOfRows());
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
		s_Buffer[m_Pointer++] = matrix.get(0, 0);
		s_Buffer[m_Pointer++] = matrix.get(0, 1);
		s_Buffer[m_Pointer++] = matrix.get(0, 2);
		s_Buffer[m_Pointer++] = matrix.get(0, 3);
		s_Buffer[m_Pointer++] = matrix.get(1, 0);
		s_Buffer[m_Pointer++] = matrix.get(1, 1);
		s_Buffer[m_Pointer++] = matrix.get(1, 2);
		s_Buffer[m_Pointer++] = matrix.get(1, 3);
		s_Buffer[m_Pointer++] = matrix.get(2, 0);
		s_Buffer[m_Pointer++] = matrix.get(2, 1);
		s_Buffer[m_Pointer++] = matrix.get(2, 2);
		s_Buffer[m_Pointer++] = matrix.get(2, 3);
		s_Buffer[m_Pointer++] = matrix.get(3, 0);
		s_Buffer[m_Pointer++] = matrix.get(3, 1);
		s_Buffer[m_Pointer++] = matrix.get(3, 2);
		s_Buffer[m_Pointer++] = matrix.get(3, 3);
	}

	void ParticleRenderer::updateTexCoordInfo(Particle& particle) {
		s_Buffer[m_Pointer++] = particle.getCurrentUV().getX();
		s_Buffer[m_Pointer++] = particle.getCurrentUV().getY();
		s_Buffer[m_Pointer++] = particle.getBlendUV().getX();
		s_Buffer[m_Pointer++] = particle.getBlendUV().getY();
		s_Buffer[m_Pointer++] = particle.getBlend();
	}

	void ParticleRenderer::updateProjectionMatrix(Window& window) {
		m_Shader.start();
		m_Shader.loadProjectionMatrix(Matrix4f().createProjectionMatrix(window.getWindow()));
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
		m_Shader.stop();
	}

}
