#pragma once
#include "../Shaders/ShaderProgram.h"

namespace Pressure {

	class ShadowShader : public ShaderProgram {

	private: 
		int location_mvpMatrix;

	public: 
		ShadowShader();
		void getAllUniformLocations() override;
		void loadMvpMatrix(Matrix4f& matrix);
		void bindAttributes() override;

	};

}