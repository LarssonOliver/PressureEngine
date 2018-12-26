#include "FrameBuffer.h"

namespace Pressure {

	FrameBuffer::FrameBuffer(Window& const window, unsigned int width, unsigned int height, unsigned int targetCount, unsigned int samples, DepthBufferType depthType) 
		: m_Window(window), m_Width(width), m_Height(height), m_TargetCount(targetCount) {
		
		createFrameBuffer();

		if (samples <= 1) {
			createColorTextureAttachments(targetCount);
			m_MultiSampled = false;
		} else {
			createMultisampleColorBufferAttachments(targetCount, samples);
			m_MultiSampled = true;
		}

		if (depthType == DepthBufferType::TEXTURE)
			createDepthTextureAttachment();
		else if (depthType == DepthBufferType::RENDER_BUFFER)
			createDepthBufferAttachment(samples);

		unbind();
	}

	FrameBuffer::~FrameBuffer() {
		glDeleteFramebuffers(1, &m_ID);		
		if (m_ColorTextureIDs.size())
			glDeleteTextures(m_ColorTextureIDs.size(), &m_ColorTextureIDs[0]);
		if (m_ColorBufferIDs.size())
			glDeleteRenderbuffers(m_ColorBufferIDs.size(), &m_ColorBufferIDs[0]);
		glDeleteTextures(1, &m_DepthTextureID);
		glDeleteRenderbuffers(1, &m_DepthBufferID);
	}
	
	void FrameBuffer::bind() const {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_ID);
		glViewport(0, 0, m_Width, m_Height);
	}

	void FrameBuffer::unbind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, m_Window.getWidth(), m_Window.getHeight());
	}

	void FrameBuffer::resolve(unsigned int readBuffer, FrameBuffer& buffer) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, buffer.getID());
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ID);
		glReadBuffer(GL_COLOR_ATTACHMENT0 + readBuffer);
		glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, buffer.getWidth(), buffer.getHeight(), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		unbind();
	}

	void FrameBuffer::resolve(unsigned int readBuffer) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ID);
		glReadBuffer(GL_COLOR_ATTACHMENT0 + readBuffer);
		glDrawBuffer(GL_BACK);
		glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, m_Window.getWidth(), m_Window.getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
		unbind();
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

	unsigned int FrameBuffer::getColorTexture(unsigned int attachment) const {
		return m_ColorTextureIDs[attachment];
	}

	unsigned int FrameBuffer::getDepthTexture() const {
		return m_DepthTextureID;
	}

	bool FrameBuffer::isMultisampled() const {
		return m_MultiSampled;
	}

	void FrameBuffer::createFrameBuffer() {
		glGenFramebuffers(1, &m_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		determineDrawBuffers();
	}

	void FrameBuffer::determineDrawBuffers() {
		std::vector<unsigned int> drawBuffers;
		drawBuffers.resize(m_TargetCount);
		for (int i = 0; i < m_TargetCount; i++) {
			drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
		}
		glDrawBuffers(m_TargetCount, &drawBuffers[0]);
	}

	void FrameBuffer::createColorTextureAttachments(unsigned int count) {
		m_ColorTextureIDs.resize(count);
		glGenTextures(count, &m_ColorTextureIDs[0]);
		
		for (unsigned int i = 0; i < count; i++) {
			glBindTexture(GL_TEXTURE_2D, m_ColorTextureIDs[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_ColorTextureIDs[i], 0);
		}
	}

	void FrameBuffer::createMultisampleColorBufferAttachments(unsigned int count, unsigned int samples) {
		m_ColorBufferIDs.resize(count);
		glGenRenderbuffers(count, &m_ColorBufferIDs[0]);

		for (unsigned int i = 0; i < count; i++) {
			glBindRenderbuffer(GL_RENDERBUFFER, m_ColorBufferIDs[i]);
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_RGBA8, m_Width, m_Height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_RENDERBUFFER, m_ColorBufferIDs[i]);
		}
	}

	void FrameBuffer::createDepthTextureAttachment() {
		glGenTextures(1, &m_DepthTextureID);
		glBindTexture(GL_TEXTURE_2D, m_DepthTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTextureID, 0);
	}

	void FrameBuffer::createDepthBufferAttachment(unsigned int samples) {
		glGenRenderbuffers(1, &m_DepthBufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBufferID);
		if (samples <= 1)
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, m_Width, m_Height);
		else
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH_COMPONENT32, m_Width, m_Height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBufferID);
	}

}