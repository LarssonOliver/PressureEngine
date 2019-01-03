#include "EntityRenderer.h"
#include "../Textures\TextureManager.h"
#include "../MasterRenderer.h"

namespace Pressure {
	
	EntityRenderer::EntityRenderer(EntityShader& shader, GLFWwindow* window)
		: m_Shader(shader), m_Window(window), m_WindModifier(0) {
		updateProjectionMatrix(shader);
	}

	void EntityRenderer::render(std::unordered_map<TexturedModel, std::vector<Entity>>& entities, Camera& camera) {
		Matrix4f viewMatrix = Matrix4f().createViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw(), camera.getRoll());
		m_Shader.loadViewMatrix(viewMatrix);
		ViewFrustum::Inst().extractPlanes(m_ProjectionMatrix.mul(viewMatrix, Matrix4f()));
		for (auto const& model : entities) {
			prepareTexturedModel(model.first);
			std::vector<Entity>& batch = entities[model.first];
			for (Entity& entity : batch) {
				if (ViewFrustum::Inst().sphereInFrustum(entity.getBounds().getCenter(), entity.getBounds().getRadius() * 1.1f)) {
					m_Shader.loadTransformationMatrix(Matrix4f().createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale()));
					glDrawElements(GL_TRIANGLES, model.first.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
				}
			}
			unbindTexturedModel(model.first.getRawModel());
		}
	}

	void EntityRenderer::updateProjectionMatrix(EntityShader& shader) {
		m_ProjectionMatrix.createProjectionMatrix(m_Window);
		shader.start();
		shader.loadProjectionmatrix(m_ProjectionMatrix);
		shader.stop();
	}

	void EntityRenderer::tick() {
		m_WindModifier += 0.005f;
		if (m_WindModifier > 360)
			m_WindModifier -= 360;
	}

	void EntityRenderer::prepareTexturedModel(const TexturedModel& texturedModel) {
		RawModel& model = texturedModel.getRawModel();
		model.getVertexArray().bind();
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glActiveTexture(GL_TEXTURE0);
		if (texturedModel.getTexture().hasTransparency()) 
			MasterRenderer::disableCulling();
		if (texturedModel.getRawModel().isWindAffected())
			m_Shader.loadWindModifier(m_WindModifier);
		else m_Shader.loadWindModifier(0);
		m_Shader.loadShineVariables(texturedModel.getTexture().getShineDamper(), texturedModel.getTexture().getReflectivity());
		m_Shader.loadFakeLighting(texturedModel.getTexture().useFakeLighting());
		TextureManager::Inst()->BindTexture(texturedModel.getTexture().getID());
		setTexParams();
	}

	void EntityRenderer::unbindTexturedModel(const RawModel& model) {
		MasterRenderer::enableCulling();
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		model.getVertexArray().unbind();
	}

	void EntityRenderer::setTexParams() const {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

}