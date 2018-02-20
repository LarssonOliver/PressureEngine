#pragma once

#include "../../Shaders/ShaderProgram.h"

namespace Pressure {

	class ContrastShader : public ShaderProgram {

	private: 
		static const std::string s_VertexShader;
		static const std::string s_FragmentShader;

	public:
		ContrastShader();
		void getAllUniformLocations() override {}
		void bindAttributes() override;

	};

}