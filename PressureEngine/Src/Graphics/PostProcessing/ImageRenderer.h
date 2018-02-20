#pragma once

#include <memory>
#include "../GLObjects/FrameBuffer.h"

namespace Pressure {

	class ImageRenderer {

	private:
		std::unique_ptr<FrameBuffer> m_Buffer;

	public:
		ImageRenderer() { }
		ImageRenderer(unsigned int width, unsigned int height, Window& window);
		
		void render();
		unsigned int getOutputTexture();

	};

}