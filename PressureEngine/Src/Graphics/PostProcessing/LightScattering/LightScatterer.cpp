#include "LightScatterer.h"

namespace Pressure {

	LightScatterer::LightScatterer(unsigned int targetWidth, unsigned int targetHeight, Window& window)
		: m_Renderer(targetWidth, targetHeight, window), m_Shader() {
	}

	void LightScatterer::render(unsigned int texture) {
		m_Shader.start();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		m_Renderer.render();
		m_Shader.stop();
	}

	unsigned int LightScatterer::getResult() {
		return m_Renderer.getOutputTexture();
	}

}