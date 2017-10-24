#pragma once
#include <GL\glew.h>
#include "../Window.h"

namespace Pressure {

	class ShadowFrameBuffer {

	private:
		const int WIDTH, HEIGHT;
		Window& window;
		unsigned int fbo;
		unsigned int shadowMap;

	public:
		ShadowFrameBuffer(int width, int height, Window& window);
		~ShadowFrameBuffer();
		void bind();
		void unbind();
		unsigned int getShadowMap();
		void init();

	private:
		static void bind(int buffer, int width, int height);
		static unsigned int createFrameBuffer();
		static unsigned int createDepthBufferAttachment(int width, int height);
	
	};

}