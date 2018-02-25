#pragma once

#include "../ImageRenderer.h"
#include "DepthOfFieldShader.h"
#include "../../Window.h"

namespace Pressure {

	class DepthOfField {

	private:
		ImageRenderer m_Renderer;
		DepthOfFieldShader m_Shader;

	public:
		DepthOfField(unsigned int targetWidth, unsigned int targetHeight, Window& window);
		void render(unsigned int colorTexture, unsigned int depthTexture);
		unsigned int getResult() const;

	};

}