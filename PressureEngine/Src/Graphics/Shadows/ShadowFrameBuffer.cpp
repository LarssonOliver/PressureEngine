
#include "ShadowFrameBuffer.h"

namespace Pressure {

	ShadowFrameBuffer::ShadowFrameBuffer(int width, int height, Window& window) 
		: WIDTH(width), HEIGHT(height), window(window) {
		init();
	}

	ShadowFrameBuffer::~ShadowFrameBuffer() {
		glDeleteFramebuffers(1, &fbo);
		glDeleteTextures(1, &shadowMap);
	}

	void ShadowFrameBuffer::bind() {
		bind(fbo, WIDTH, HEIGHT);
	}

	void ShadowFrameBuffer::unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, window.getWidth(), window.getHeight());
	}

	unsigned int ShadowFrameBuffer::getShadowMap() {
		return shadowMap;
	}

	void ShadowFrameBuffer::init() {
		fbo = createFrameBuffer();
		shadowMap = createDepthBufferAttachment(WIDTH, HEIGHT);
		unbind();
	}

	void ShadowFrameBuffer::bind(int buffer, int width, int height) {
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_DRAW_BUFFER, buffer);
		glViewport(0, 0, width, height);
	}

	int ShadowFrameBuffer::createFrameBuffer() {
		GLuint fbo;
		glGenBuffers(1, &fbo);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		return fbo;
	}

	int ShadowFrameBuffer::createDepthBufferAttachment(int width, int height) {
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
		return texture;
	}

}
