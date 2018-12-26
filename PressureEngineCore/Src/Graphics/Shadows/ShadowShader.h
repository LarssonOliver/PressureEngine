#pragma once
#include "../Shaders/Shader.h"

namespace Pressure {

	class ShadowShader : public Shader {

	private: 
		int location_mvpMatrix;

	public: 
		ShadowShader();
		void getAllUniformLocations() override;
		void loadMvpMatrix(Matrix4f& matrix);
		void bindAttributes() override;

	};

}