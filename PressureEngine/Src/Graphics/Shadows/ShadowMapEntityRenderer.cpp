#include "ShadowMapEntityRenderer.h"

namespace Pressure {

	ShadowMapEntityRenderer::ShadowMapEntityRenderer(ShadowShader& shader, Matrix4f& projectionViewMatrix) 
		: shader(shader), projectionViewMatrix(projectionViewMatrix) {		
	}

	void ShadowMapEntityRenderer::render(const std::map<TexturedModel, std::vector<Entity>>& entities) {
		for (const auto& model : entities) {
			bindModel(*model.first.getRawModel());
			for (const auto& entity : model.second) {
				prepareInstance(entity);
				glDrawElements(GL_TRIANGLES, model.first.getRawModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
			}
		}
		glDisableVertexAttribArray(0);
		glBindVertexArray(NULL);
	}

	void ShadowMapEntityRenderer::bindModel(const RawModel& rawModel) {
		glBindVertexArray(rawModel.getVaoID());
		glEnableVertexAttribArray(0);
	}

	void ShadowMapEntityRenderer::prepareInstance(const Entity& entity) {
		Matrix4f modelMatrix;
		modelMatrix.createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
		shader.loadMvpMatrix(modelMatrix.mul(projectionViewMatrix));
	}

}