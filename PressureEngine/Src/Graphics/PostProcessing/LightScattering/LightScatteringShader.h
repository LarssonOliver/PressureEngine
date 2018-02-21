#pragma once

#include "../../Shaders/ShaderProgram.h"

namespace Pressure {

	class LightScatteringShader : public ShaderProgram {

	private: 
		static const std::string s_VertexShader;
		static const std::string s_FragmentShader;

	public:
		LightScatteringShader();
		void getAllUniformLocations() override {}
		void bindAttributes() override;

	};

}