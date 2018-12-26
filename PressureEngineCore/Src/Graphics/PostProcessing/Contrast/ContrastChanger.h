#pragma once

#include "../ImageRenderer.h"
#include "ContrastShader.h"

namespace Pressure {

	class ContrastChanger {

	private:
		ImageRenderer m_Renderer;
		ContrastShader m_Shader;

	public:
		void render(unsigned int texture);

	};

}