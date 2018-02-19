#pragma once

#include <GL\glew.h>
#include "../Window.h"

namespace Pressure {

	enum DepthBufferType {
		NONE,
		TEXTURE,
		RENDER_BUFFER
	};

	class FrameBuffer {
		 
	private:
		Window& m_Window;

		unsigned int m_ID;

		unsigned int m_ColorBufferID;
		unsigned int m_DepthBufferID;

		unsigned int m_ColorTextureID;
		unsigned int m_DepthTextureID;

		unsigned int m_Width;
		unsigned int m_Height;

	public:
		FrameBuffer(Window& window, unsigned int width, unsigned int height, DepthBufferType type);
		~FrameBuffer();

		void bind() const;
		void unbind() const;
		void bindToRead() const;

		unsigned int getColorTexture() const;
		unsigned int getDepthTexture() const;

	private:
		void createFrameBuffer();
		void createColorTextureAttachment();
		void createDepthTextureAttachment();
		void createDepthBufferAttachment();

	};

}
