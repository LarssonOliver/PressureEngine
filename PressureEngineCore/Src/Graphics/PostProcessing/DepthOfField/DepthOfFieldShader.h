#pragma once

#include "../../Shaders/Shader.h"

namespace Pressure {

	class DepthOfFieldShader : public Shader {

	private: 
		static const std::string s_VertexShader;
		static const std::string s_FragmentShader;

		unsigned int location_colorTexture;
		unsigned int location_depthTexture;
		unsigned int location_targetSize;

	public:
		DepthOfFieldShader();
		void getAllUniformLocations() override;
		void bindAttributes() override;
		void connectTextureUnits();

		void loadTargetSize(Vector2f& targetSize);

	};

}