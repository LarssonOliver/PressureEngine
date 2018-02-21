#pragma once

#include "../../Shaders/ShaderProgram.h"

namespace Pressure {

	class LightScatteringShader : public ShaderProgram {

	private: 
		static const std::string s_VertexShader;
		static const std::string s_FragmentShader;

		unsigned int location_lightPositionOnScreen;

	public:
		LightScatteringShader();
		void getAllUniformLocations() override;
		void bindAttributes() override;

		void loadLightPosition(Vector2f& lightPosition);

	};

}