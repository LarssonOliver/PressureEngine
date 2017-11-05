#include "ShadowMapEntityRenderer.h"
#include "../MasterRenderer.h"
#include <iostream>

namespace Pressure {

	ShadowMapEntityRenderer::ShadowMapEntityRenderer(ShadowShader& shader, Matrix4f& projectionViewMatrix) 
		: shader(shader), projectionViewMatrix(projectionViewMatrix) {		
	}

	void ShadowMapEntityRenderer::render(const std::map<TexturedModel, std::vector<Entity>>& entities) {
		for (const auto& model : entities) {
			bindModel(*model.first.getRawModel());
			if (model.first.getTexture()->isHasTransparency())
				MasterRenderer::disableCulling();
			for (const auto& entity : model.second) {
				prepareInstance(entity);
				glDrawElements(GL_TRIANGLES, model.first.getRawModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
			}
			if (model.first.getTexture()->isHasTransparency())
				MasterRenderer::enableCulling();
		}
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	void ShadowMapEntityRenderer::bindModel(const RawModel& rawModel) {
		glBindVertexArray(rawModel.getVaoID());
		glEnableVertexAttribArray(0);
	}

	void ShadowMapEntityRenderer::prepareInstance(const Entity& entity) {
		Matrix4f modelMatrix;
		modelMatrix.createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
		shader.loadMvpMatrix(modelMatrix.mul(projectionViewMatrix));	
		//shader.loadMvpMatrix(Matrix4f().createTransformationMatrix(Vector3f(0, 0, 0), entity.getRotation(), 1));
		
	}

}