#pragma once

#include "../../Shaders/Shader.h"

namespace Pressure {

	class LightScatteringShader : public Shader {

	private: 
		static const std::string s_VertexShader;
		static const std::string s_FragmentShader;

		unsigned int location_lightPositionOnScreen;
		unsigned int location_lightTexture;
		unsigned int location_colorTexture;

	public:
		LightScatteringShader();
		void getAllUniformLocations() override;
		void bindAttributes() override;

		void connectTextureUnits();
		void loadLightPosition(Vector2f& lightPosition);

	};

}