#pragma once

#include <GL\glew.h>
#include "../Window.h"
#include "../../DllExport.h"

namespace Pressure {

	enum PRESSURE_API DepthBufferType {
		NONE,
		TEXTURE,
		RENDER_BUFFER
	};

	class PRESSURE_API FrameBuffer {
		 
	private:
		Window& m_Window;

		unsigned int m_ID;

		unsigned int m_ColorBufferID[2];
		unsigned int m_DepthBufferID;

		unsigned int m_ColorTextureID;
		unsigned int m_DepthTextureID;

		unsigned int m_Width;
		unsigned int m_Height;

		bool m_MultiTarget;

	public:
		FrameBuffer(Window& window, unsigned int width, unsigned int height, DepthBufferType type);
		FrameBuffer(Window& window, unsigned int width, unsigned int height, bool multiTarget);
		~FrameBuffer();

		void bind() const;
		void unbind() const;
		void bindToRead() const;

		void resolveToFrameBuffer(unsigned int readBuffer, FrameBuffer& buffer);
		void resolveToScreen(unsigned int readBuffer);

		unsigned int getColorTexture() const;
		unsigned int getDepthTexture() const;
		unsigned int getID() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;

	private:
		void createFrameBuffer();
		void determineDrawBuffers();

		void createColorTextureAttachment();
		unsigned int createMultisampleColorAttachment(unsigned int attachment);

		void createDepthTextureAttachment();
		void createDepthBufferAttachment();

	};

}
