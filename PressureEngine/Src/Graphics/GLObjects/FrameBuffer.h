#pragma once

#include <GL\glew.h>
#include <vector>
#include "../../DllExport.h"
#include "../Window.h"

namespace Pressure {

	class PRESSURE_API FrameBuffer {

	public:
		static enum DepthBufferType {
			NONE,
			TEXTURE,
			RENDER_BUFFER
		};

	private:
		Window & const m_Window;

		unsigned int m_ID;

		unsigned int m_Width;
		unsigned int m_Height;

		unsigned int m_TargetCount;

		std::vector<unsigned int> m_ColorBufferIDs;
		std::vector<unsigned int> m_ColorTextureIDs;

		unsigned int m_DepthBufferID;
		unsigned int m_DepthTextureID;

		bool m_MultiSampled;

	public:
		FrameBuffer(Window& const window, unsigned int width, unsigned int height, unsigned int targetCount, unsigned int samples, DepthBufferType depthType);
		~FrameBuffer();

		void bind() const;
		void unbind() const;

		void resolve(unsigned int readBuffer, FrameBuffer& buffer); // Resolves to other framebuffer;
		void resolve(unsigned int readBuffer); // Resolves to screen;

		unsigned int getID() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;
		unsigned int getColorTexture(unsigned int attachment = 0) const;
		unsigned int getDepthTexture() const;
		bool isMultisampled() const;

	private:
		void createFrameBuffer();
		void determineDrawBuffers();

		void createColorTextureAttachments(unsigned int count);
		void createMultisampleColorBufferAttachments(unsigned int count, unsigned int samples);

		void createDepthTextureAttachment();
		void createDepthBufferAttachment(unsigned int samples);

	};

}