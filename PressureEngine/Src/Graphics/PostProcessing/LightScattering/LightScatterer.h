#pragma once

#include "../ImageRenderer.h"
#include "LightScatteringShader.h"

namespace Pressure {

	class LightScatterer {

	private:
		ImageRenderer m_Renderer;
		LightScatteringShader m_Shader;

	public:
		LightScatterer(unsigned int targetWidth, unsigned int targetHeight, Window& window);
		void render(unsigned int texture);
		unsigned int getResult();

	};

}