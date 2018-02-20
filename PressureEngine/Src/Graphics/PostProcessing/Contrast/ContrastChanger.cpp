#include "ContrastChanger.h"

namespace Pressure {

	void ContrastChanger::render(unsigned int texture) {
		m_Shader.start();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		m_Renderer.render();
		m_Shader.stop();
	}

}