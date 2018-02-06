#include "Renderer.h"
#include "../Textures\TextureManager.h"
#include "../MasterRenderer.h"

namespace Pressure {
	
	Renderer::Renderer(EntityShader& shader, GLFWwindow* window)
		: shader(shader), window(window), windModifier(0) {
		updateProjectionMatrix(shader);
	}

	void Renderer::render(std::map<TexturedModel, std::vector<Entity>>& entities, Matrix4f& toShadowSpace) {
		shader.loadToShadowMapSpace(toShadowSpace);
		for (auto const& model : entities) {
			prepareTexturedModel(model.first);
			std::vector<Entity>& batch = entities[model.first];
			for (Entity& entity : batch) {
				prepareInstance(entity);
				glDrawElements(GL_TRIANGLES, model.first.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
			}
			unbindTexturedModel(model.first.getRawModel());
		}
	}

	void Renderer::updateProjectionMatrix(EntityShader& shader) {
		projectionMatrix.createProjectionMatrix(window);
		shader.start();
		shader.loadProjectionmatrix(projectionMatrix);
		shader.stop();
	}

	void Renderer::tick() {
		windModifier += 0.005;
		if (windModifier > 360)
			windModifier -= 360;
	}

	void Renderer::prepareTexturedModel(const TexturedModel& texturedModel) {
		RawModel& model = texturedModel.getRawModel();
		model.getVertexArray().bind();
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glActiveTexture(GL_TEXTURE0);
		if (texturedModel.getTexture().hasTransparency()) 
			MasterRenderer::disableCulling();
		if (texturedModel.getRawModel().isWindAffected())
			shader.loadWindModifier(windModifier);
		else shader.loadWindModifier(0);
		shader.loadShineVariables(texturedModel.getTexture().getShineDamper(), texturedModel.getTexture().getReflectivity());
		shader.loadFakeLighting(texturedModel.getTexture().useFakeLighting());
		TextureManager::Inst()->BindTexture(texturedModel.getTexture().getID());
		setTexParams();
	}

	void Renderer::unbindTexturedModel(const RawModel& model) {
		MasterRenderer::enableCulling();
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		model.getVertexArray().unbind();
	}

	void Renderer::prepareInstance(Entity& entity) {
		shader.loadTransformationMatrix(Matrix4f().createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale()));
	}

	void Renderer::setTexParams() const {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

}