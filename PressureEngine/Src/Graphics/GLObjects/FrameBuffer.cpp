#include "FrameBuffer.h"

namespace Pressure {

	FrameBuffer::FrameBuffer(Window& window, unsigned int width, unsigned int height, DepthBufferType type)
		: m_Window(window), m_Width(width), m_Height(height), m_MultiTarget(false) {
		createFrameBuffer();	
		createColorTextureAttachment();
		if (type == DepthBufferType::RENDER_BUFFER)
			createDepthBufferAttachment();
		else if (type == DepthBufferType::TEXTURE)
			createDepthTextureAttachment();		
		unbind();
	}

	FrameBuffer::FrameBuffer(Window& window, unsigned int width, unsigned int height, bool multiTarget) 
		: m_Window(window), m_Width(width), m_Height(height), m_MultiTarget(multiTarget) {
		createFrameBuffer();

		m_ColorBufferID[0] = createMultisampleColorAttachment(GL_COLOR_ATTACHMENT0);
		if (m_MultiTarget) {
			m_ColorBufferID[1] = createMultisampleColorAttachment(GL_COLOR_ATTACHMENT1);
		} else
			createColorTextureAttachment();
		
		createDepthBufferAttachment();
		unbind();
	}

	FrameBuffer::~FrameBuffer() {
		glDeleteFramebuffers(1, &m_ID);
		glDeleteTextures(1, &m_ColorTextureID);
		glDeleteTextures(1, &m_DepthTextureID);
		glDeleteRenderbuffers(m_MultiTarget ? 2 : 1, m_ColorBufferID);
		glDeleteRenderbuffers(1, &m_DepthBufferID);
	}

	void FrameBuffer::bind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_ID);
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

	void FrameBuffer::resolveToFrameBuffer(unsigned int readBuffer, FrameBuffer& buffer) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, buffer.getID());
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ID);
		glReadBuffer(readBuffer);
		glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, buffer.getWidth(), buffer.getHeight(), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		unbind();
	}

	void FrameBuffer::resolveToScreen() {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ID);
		glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, m_Window.getWidth(), m_Window.getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
		unbind();
	}

	unsigned int FrameBuffer::getColorTexture() const {
		return m_ColorTextureID;
	}

	unsigned int FrameBuffer::getDepthTexture() const {
		return m_DepthTextureID;
	}

	unsigned int FrameBuffer::getID() const {
		return m_ID;
	}

	unsigned int FrameBuffer::getWidth() const {
		return m_Width;
	}

	unsigned int FrameBuffer::getHeight() const {
		return m_Height;
	}

	void FrameBuffer::createFrameBuffer() {
		glGenFramebuffers(1, &m_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		determineDrawBuffers();
	}

	void FrameBuffer::determineDrawBuffers() {
		unsigned int drawBuffers[2] = { GL_COLOR_ATTACHMENT0, 0 };
		if (m_MultiTarget)
			drawBuffers[1] = GL_COLOR_ATTACHMENT1;
		glDrawBuffers(2, drawBuffers);
	}

	void FrameBuffer::createColorTextureAttachment() {
		glGenTextures(1, &m_ColorTextureID);
		glBindTexture(GL_TEXTURE_2D, m_ColorTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorTextureID, 0);
	}

	unsigned int FrameBuffer::createMultisampleColorAttachment(unsigned int attachment) {
		unsigned int ID;
		glGenRenderbuffers(1, &ID);
		glBindRenderbuffer(GL_RENDERBUFFER, ID);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGBA8, m_Width, m_Height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, ID);
		return ID;
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