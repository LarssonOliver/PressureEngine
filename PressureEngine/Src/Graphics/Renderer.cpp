#include "Renderer.h"

namespace Pressure {
	
	Renderer::Renderer(StaticShader& shader, GLFWwindow* window) {
		updateProjectionMatrix(shader, window);
	}

	void Renderer::prepare() const {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5, 0.5, 0.5, 1);
	}

	void Renderer::render(const Entity& entity, StaticShader& shader) const {
		TexturedModel& texturedModel = entity.getTexturedModel();
		RawModel model = *texturedModel.getRawModel();
		model.getVao()->bind();
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		Matrix4f transformationMatrix;
		transformationMatrix.createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
		shader.loadTransformationMatrix(transformationMatrix);
		glActiveTexture(GL_TEXTURE0);
		TextureManager::Inst()->BindTexture(texturedModel.getTexture()->getID());
		setTexParams();
		glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0); 
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		model.getVao()->unbind();
	}

	void Renderer::updateProjectionMatrix(StaticShader& shader, GLFWwindow* window) {
		projectionMatrix.createProjectionMatrix(window);
		shader.start();
		shader.loadProjectionmatrix(projectionMatrix);
		shader.stop();
	}

	void Renderer::setTexParams() const {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

}