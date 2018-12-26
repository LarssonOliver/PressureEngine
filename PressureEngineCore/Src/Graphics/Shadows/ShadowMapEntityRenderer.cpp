#include "ShadowMapEntityRenderer.h"
#include "../MasterRenderer.h"

namespace Pressure {

	ShadowMapEntityRenderer::ShadowMapEntityRenderer(ShadowShader& shader, Matrix4f& projectionViewMatrix) 
		: m_Shader(shader), m_ProjectionViewMatrix(projectionViewMatrix) {		
	}

	void ShadowMapEntityRenderer::render(const std::unordered_map<TexturedModel, std::vector<Entity>>& entities) {
		MasterRenderer::enableFrontFaceCulling();
		for (const auto& model : entities) {
			model.first.getRawModel().getVertexArray().bind();
			glEnableVertexAttribArray(0);
			if (model.first.getTexture().hasTransparency())
				MasterRenderer::disableCulling();
			for (const auto& entity : model.second) {
				prepareInstance(entity);
				glDrawElements(GL_TRIANGLES, model.first.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
			}
			if (model.first.getTexture().hasTransparency())
				MasterRenderer::enableFrontFaceCulling();
		}
		MasterRenderer::enableCulling();
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	void ShadowMapEntityRenderer::prepareInstance(const Entity& entity) {
		Matrix4f modelMatrix = Matrix4f().createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
		m_Shader.loadMvpMatrix(m_ProjectionViewMatrix.mul(modelMatrix, Matrix4f()));	
	}

}