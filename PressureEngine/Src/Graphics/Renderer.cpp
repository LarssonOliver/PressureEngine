#include "Renderer.h"
#include "Textures\TextureManager.h"

namespace Pressure {
	
	Renderer::Renderer(StaticShader& shader, GLFWwindow* window)
		: shader(shader), window(window)
	{
		updateProjectionMatrix(shader);
	}

	void Renderer::prepare() const {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5, 0.5, 0.5, 1);
	}

	void Renderer::render(std::map<TexturedModel, std::vector<Entity>>& entities) {
		for (auto const& model : entities) {
			prepareTexturedModel(model.first);
			std::vector<Entity>& batch = entities.at(model.first);
			for (Entity& entity : batch) {
				prepareInstance(entity);
				glDrawElements(GL_TRIANGLES, model.first.getRawModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
			}
			unbindTexturedModel(*model.first.getRawModel());
		}
	}

	void Renderer::updateProjectionMatrix(StaticShader& shader) {
		projectionMatrix.createProjectionMatrix(window);
		shader.start();
		shader.loadProjectionmatrix(projectionMatrix);
		shader.stop();
	}

	void Renderer::prepareTexturedModel(const TexturedModel& texturedModel) {
		RawModel& model = *texturedModel.getRawModel();
		model.getVao()->bind();
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glActiveTexture(GL_TEXTURE0);
		TextureManager::Inst()->BindTexture(texturedModel.getTexture()->getID());
		setTexParams();
	}

	void Renderer::unbindTexturedModel(const RawModel& model) {
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		model.getVao()->unbind();
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