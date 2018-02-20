#include "ImageRenderer.h"

namespace Pressure {

	ImageRenderer::ImageRenderer(unsigned int width, unsigned int height, Window& window) {
		m_Buffer = std::make_unique<FrameBuffer>(window, width, height, DepthBufferType::NONE);
	}

	void ImageRenderer::render() {
		if (m_Buffer)
			m_Buffer->bind();
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		if (m_Buffer)
			m_Buffer->unbind();
	}

	unsigned int ImageRenderer::getOutputTexture() {
		return m_Buffer->getColorTexture();
	}

}
