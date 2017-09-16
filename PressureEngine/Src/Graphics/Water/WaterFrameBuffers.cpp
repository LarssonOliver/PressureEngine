#include "WaterFrameBuffers.h"

namespace Pressure {

	WaterFrameBuffers::WaterFrameBuffers(GLFWwindow* window) : window(window) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		REFLECTION_WIDTH = width / 4;
		REFLECTION_HEIGHT = height / 4;
		REFRACTION_WIDTH = width / 2;
		REFRACTION_HEIGHT = height / 2;

		initReflectionFrameBuffer();
		initRefractionFrameBuffer();
	}

	WaterFrameBuffers::~WaterFrameBuffers() {
		glDeleteFramebuffers(1, &reflectionFrameBuffer);
		glDeleteTextures(1, &reflectionTexture);
		glDeleteRenderbuffers(1, &reflectionDepthBuffer);

		glDeleteFramebuffers(1, &refractionFrameBuffer);
		glDeleteTextures(1, &refractionTexture);
		glDeleteTextures(1, &refractionDepthTexture);
	}

	void WaterFrameBuffers::bindReflectionFrameBuffer() {
		bindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
	}

	void WaterFrameBuffers::bindRefractionFrameBuffer() {
		bindFrameBuffer(refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
	}

	void WaterFrameBuffers::unbindFrameBuffer() {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glBindFramebuffer(GL_FRAMEBUFFER, NULL);
		glViewport(0, 0, width, height);
	}

	GLuint WaterFrameBuffers::getReflectionTexture() const {
		return reflectionTexture;
	}

	GLuint WaterFrameBuffers::getRefractionTexture() const {
		return refractionTexture;
	}

	GLuint WaterFrameBuffers::getRefractionDepthTexture() const {
		return refractionDepthTexture;
	}

	void WaterFrameBuffers::initReflectionFrameBuffer() {
		reflectionFrameBuffer = createFrameBuffer();
		reflectionTexture = createTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
		reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
		unbindFrameBuffer();
	}

	void WaterFrameBuffers::initRefractionFrameBuffer() {
		refractionFrameBuffer = createFrameBuffer();
		refractionTexture = createTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
		refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
		unbindFrameBuffer();
	}

	void WaterFrameBuffers::bindFrameBuffer(GLuint frameBuffer, int width, int height) {
		glBindTexture(GL_TEXTURE_2D, NULL);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glViewport(0, 0, width, height);
	}

	GLuint WaterFrameBuffers::createFrameBuffer() {
		GLuint frameBuffer;
		glGenFramebuffers(1, &frameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		return frameBuffer;
	}

	GLuint WaterFrameBuffers::createTextureAttachment(int width, int height) {
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
		return texture;
	}

	GLuint WaterFrameBuffers::createDepthTextureAttachment(int width, int height) {
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
		return texture;
	}

	GLuint WaterFrameBuffers::createDepthBufferAttachment(int width, int height) {
		GLuint depthBuffer;
		glGenRenderbuffers(1, &depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
		return depthBuffer;
	}

}
