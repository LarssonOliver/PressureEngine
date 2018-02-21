#include "LightScatterer.h"

namespace Pressure {

	LightScatterer::LightScatterer(unsigned int targetWidth, unsigned int targetHeight, Window& window)
		: m_Window(window), m_Renderer(targetWidth, targetHeight, window), m_Shader() {
		m_ProjectionMatrix.createProjectionMatrix(window.getWindow());
	}

	void LightScatterer::render(unsigned int colorTexture, unsigned int lightTexture, Vector3f& lightPosition, Camera& camera) {
		Matrix4f viewMatrix = Matrix4f().createViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw(), camera.getRoll());
		Vector4f coords(lightPosition, 1.0);
		viewMatrix.transform(coords, coords);
		m_ProjectionMatrix.transform(coords, coords);
		Vector2f screenPos;
		if (coords.w < 90000)
			screenPos = Vector2f(100, 0); // Looks for this in shader.
		else if (coords.w == 0)
			screenPos = Vector2f(0.5);
		else {
			screenPos = Vector2f(coords.x / coords.w, coords.y / coords.w);
			screenPos.x = (screenPos.x + 1) / 2;
			screenPos.y = (screenPos.y + 1) / 2;
		}

		m_Shader.start();
		m_Shader.connectTextureUnits();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, lightTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		m_Shader.loadLightPosition(screenPos);
		m_Renderer.render();
		m_Shader.stop();
	}

	unsigned int LightScatterer::getResult() {
		return m_Renderer.getOutputTexture();
	}

	void LightScatterer::updateProjectionMatrix() {
		m_ProjectionMatrix.createProjectionMatrix(m_Window.getWindow());
	}

}