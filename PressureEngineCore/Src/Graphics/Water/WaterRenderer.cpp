#include "WaterRenderer.h"
#include <iostream>

namespace Pressure {

	WaterRenderer::WaterRenderer(Window& window)
		: m_Window(window), m_ReflectionBuffer(window, window.getWidth() / 2, window.getHeight() / 2, 1, 1, FrameBuffer::DepthBufferType::RENDER_BUFFER), m_RefractionBuffer(window, window.getWidth() / 2, window.getHeight() / 2, 1, 1, FrameBuffer::DepthBufferType::TEXTURE), m_ReflectionResultsBuffer(window, window.getWidth() / 4, window.getHeight() / 4, 1, 1, FrameBuffer::DepthBufferType::RENDER_BUFFER), m_RefractionResultsBuffer(window, window.getWidth() / 2, window.getHeight() / 2, 1, 1, FrameBuffer::DepthBufferType::TEXTURE) {
		m_Shader.start();
		m_Shader.connectTextureUnits();
		updateProjectionmatrix();
	}

	void WaterRenderer::updateProjectionmatrix() {
		m_Shader.start();
		m_Shader.loadProjectionMatrix(Matrix4f().createProjectionMatrix(m_Window.getWindow()));
		m_Shader.stop();
	}

	void WaterRenderer::tick() {
		m_WaveModifier += 0.3f;
		if (m_WaveModifier > 360)
			m_WaveModifier -= 360;
	}

	void WaterRenderer::render(std::vector<Water>& water, std::vector<Light>& lights, Camera& camera) {
		prepare(water, lights, camera);
		for (Water& w : water) {
			m_Shader.loadTransformationMatrix(Matrix4f().createTransformationMatrix(w.getPosition(), Vector3f(0), 1));
			glDrawElements(GL_TRIANGLES, w.getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		finish(water);
	}

	FrameBuffer& WaterRenderer::getReflectionBuffer() {
		return m_ReflectionBuffer;
	}

	FrameBuffer& WaterRenderer::getRefractionBuffer() {
		return m_RefractionBuffer;
	}

	void WaterRenderer::prepare(std::vector<Water>& water, std::vector<Light>& lights, Camera& camera) {
		if (m_ReflectionBuffer.isMultisampled())
			m_ReflectionBuffer.resolve(0, m_ReflectionResultsBuffer);
		if (m_RefractionBuffer.isMultisampled())
			m_RefractionBuffer.resolve(0, m_RefractionResultsBuffer);

		m_Shader.start();
		m_Shader.loadViewMatrix(camera);
		m_Shader.loadWaveModifier((float) Math::toRadians(m_WaveModifier));
		m_Shader.loadLights(lights);
		Water::getModel().getVertexArray().bind();
		glEnableVertexAttribArray(0);

		if (m_ReflectionBuffer.isMultisampled()) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_ReflectionResultsBuffer.getColorTexture());
		} else {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_ReflectionBuffer.getColorTexture());
		}

		if (m_RefractionBuffer.isMultisampled()) {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, m_RefractionResultsBuffer.getColorTexture());
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, m_RefractionResultsBuffer.getDepthTexture());
		} else {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, m_RefractionBuffer.getColorTexture());
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, m_RefractionBuffer.getDepthTexture());
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void WaterRenderer::finish(std::vector<Water>& water) {
		glDisableVertexAttribArray(0);
		Water::getModel().getVertexArray().unbind();
		m_Shader.stop();
		glDisable(GL_BLEND);
	}

}