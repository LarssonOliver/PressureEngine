#pragma once
#include "../Shaders/ShaderProgram.h"

namespace Pressure {

	class ShadowShader : public ShaderProgram {

	private: 
		static const char* VERTEX_FILE;
		static const char* FRAGMENT_FILE;

		int location_mvpMatrix;

	public: 
		ShadowShader();
		void getAllUniformLocations() override;
		void loadMvpMatrix(Matrix4f& matrix);
		void bindAttributes() override;

	};

}