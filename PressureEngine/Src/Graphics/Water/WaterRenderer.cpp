#include "WaterRenderer.h"
#include <iostream>

namespace Pressure {

	WaterRenderer::WaterRenderer(Window& window)
		: window(window), reflectionBuffer(window, window.getWidth() / 4, window.getWidth() / 4, 1, 1, FrameBuffer::DepthBufferType::RENDER_BUFFER), refractionBuffer(window, window.getWidth() / 2, window.getHeight() / 2, 1, 1, FrameBuffer::DepthBufferType::TEXTURE) {
		shader.start();
		shader.connectTextureUnits();
		updateProjectionmatrix();
	}

	void WaterRenderer::updateProjectionmatrix() {
		shader.start();
		shader.loadProjectionMatrix(Matrix4f().createProjectionMatrix(window.getWindow()));
		shader.stop();
	}

	void WaterRenderer::tick() {
		waveModifier += 0.3f;
		if (waveModifier > 360)
			waveModifier -= 360;
	}

	void WaterRenderer::render(std::vector<Water>& water, std::vector<Light>& lights, Camera& camera) {
		prepare(water, lights, camera);
		for (Water& w : water) {
			shader.loadTransformationMatrix(Matrix4f().createTransformationMatrix(w.getPosition(), Vector3f(0), 1));
			glDrawElements(GL_TRIANGLES, w.getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		finish(water);
	}

	FrameBuffer& WaterRenderer::getReflectionBuffer() {
		return reflectionBuffer;
	}

	FrameBuffer& WaterRenderer::getRefractionBuffer() {
		return refractionBuffer;
	}

	void WaterRenderer::prepare(std::vector<Water>& water, std::vector<Light>& lights, Camera& camera) {
		shader.start();
		shader.loadViewMatrix(camera);
		shader.loadWaveModifier((float) Math::toRadians(waveModifier));
		shader.loadLights(lights);
		Water::getModel().getVertexArray().bind();
		glEnableVertexAttribArray(0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, reflectionBuffer.getColorTexture());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, refractionBuffer.getColorTexture());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, refractionBuffer.getDepthTexture());
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void WaterRenderer::finish(std::vector<Water>& water) {
		glDisableVertexAttribArray(0);
		Water::getModel().getVertexArray().unbind();
		shader.stop();
		glDisable(GL_BLEND);
	}

}