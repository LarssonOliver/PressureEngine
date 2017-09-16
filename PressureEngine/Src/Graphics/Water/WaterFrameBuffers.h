#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Pressure {

	class WaterFrameBuffers {

	private:
		GLFWwindow* window;

		int REFLECTION_WIDTH;
		int REFLECTION_HEIGHT;

		GLuint reflectionFrameBuffer;
		GLuint reflectionTexture;
		GLuint reflectionDepthBuffer;

		int REFRACTION_WIDTH;
		int REFRACTION_HEIGHT;

		GLuint refractionFrameBuffer;
		GLuint refractionTexture;
		GLuint refractionDepthTexture;

	public:
		WaterFrameBuffers(GLFWwindow* window);
		~WaterFrameBuffers();
		
		void bindReflectionFrameBuffer();
		void bindRefractionFrameBuffer();
		void unbindFrameBuffer();

		GLuint getReflectionTexture() const;
		GLuint getRefractionTexture() const;
		GLuint getRefractionDepthTexture() const;

	private: 
		void initReflectionFrameBuffer();
		void initRefractionFrameBuffer();
		
		void bindFrameBuffer(GLuint frameBuffer, int width, int height);
		GLuint createFrameBuffer();
		
		GLuint createTextureAttachment(int width, int height);
		GLuint createDepthTextureAttachment(int width, int height);
		GLuint createDepthBufferAttachment(int width, int height);

	};

}
