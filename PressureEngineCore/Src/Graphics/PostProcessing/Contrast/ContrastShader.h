#pragma once

#include "../../Shaders/Shader.h"

namespace Pressure {

	class ContrastShader : public Shader {

	private: 
		static const std::string s_VertexShader;
		static const std::string s_FragmentShader;

	public:
		ContrastShader();
		void getAllUniformLocations() override {}
		void bindAttributes() override;

	};

}