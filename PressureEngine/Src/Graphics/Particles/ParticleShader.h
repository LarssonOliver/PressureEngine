#pragma once
#include "../Shaders/ShaderProgram.h"

namespace Pressure {

	class ParticleShader : public ShaderProgram {

	private:
		static const char* VERTEX_FILE;
		static const char* FRAGMENT_FILE;

	protected:
		virtual void getAllUniformLocations() override;
		virtual void bindAttributes() override;

	public:
		void loadTransformationMatrix(Matrix4f& matrix);
		//void loadViewMatrix(Camera& camera);

	private:
		int location_transformationMatrix;
		int location_viewMatrix;

	};

}