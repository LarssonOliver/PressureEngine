#include "DepthOfField.h"

namespace Pressure {

	DepthOfField::DepthOfField(unsigned int targetWidth, unsigned int targetHeight, Window& window)  
		: m_Renderer(targetWidth, targetHeight, window) { }

	void DepthOfField::render(unsigned int colorTexture, unsigned int depthTexture) {
		m_Shader.start();
		m_Shader.connectTextureUnits();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthTexture);
		m_Renderer.render();
		m_Shader.stop();
	}

	unsigned int DepthOfField::getResult() const {
		return m_Renderer.getOutputTexture();
	}

}