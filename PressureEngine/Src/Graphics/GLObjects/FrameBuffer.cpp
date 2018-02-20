#include "FrameBuffer.h"

namespace Pressure {

	FrameBuffer::FrameBuffer(Window& window, unsigned int width, unsigned int height, DepthBufferType type)
		: m_Window(window), m_Width(width), m_Height(height) {
		createFrameBuffer();
		createColorTextureAttachment();
		if (type == DepthBufferType::RENDER_BUFFER)
			createDepthBufferAttachment();
		else if (type == DepthBufferType::TEXTURE)
			createDepthTextureAttachment();
		unbind();
	}

	FrameBuffer::~FrameBuffer() {
		glDeleteFramebuffers(1, &m_ID);
		glDeleteTextures(1, &m_ColorTextureID);
		glDeleteTextures(1, &m_DepthTextureID);
		glDeleteRenderbuffers(1, &m_ColorBufferID);
		glDeleteRenderbuffers(1, &m_DepthBufferID);
	}

	void FrameBuffer::bind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		glViewport(0, 0, m_Width, m_Height);
	}

	void FrameBuffer::unbind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, m_Window.getWidth(), m_Window.getHeight());
	}

	void FrameBuffer::bindToRead() const {
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ID);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
	}

	unsigned int FrameBuffer::getColorTexture() const {
		return m_ColorTextureID;
	}

	unsigned int FrameBuffer::getDepthTexture() const {
		return m_DepthTextureID;
	}

	void FrameBuffer::createFrameBuffer() {
		glGenFramebuffers(1, &m_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
	}

	void FrameBuffer::createColorTextureAttachment() {
		glGenTextures(1, &m_ColorTextureID);
		glBindTexture(GL_TEXTURE_2D, m_ColorTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorTextureID, 0);
	}

	void FrameBuffer::createDepthTextureAttachment() {
		glGenTextures(1, &m_DepthTextureID);
		glBindTexture(GL_TEXTURE_2D, m_DepthTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTextureID, 0);
	}

	void FrameBuffer::createDepthBufferAttachment() {
		glGenRenderbuffers(1, &m_DepthBufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, m_Width, m_Height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBufferID);
	}

}