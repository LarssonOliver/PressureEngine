#pragma once
#include "../Shaders/Shader.h"

namespace Pressure {

	class ParticleShader : public Shader {

	public:
		ParticleShader();

	protected:
		virtual void getAllUniformLocations() override;
		virtual void bindAttributes() override;

	public:
		void loadProjectionMatrix(Matrix4f& matrix);
		void loadNumberOfRows(const float numberOfRows);
		
	private:
		int location_projectionMatrix;
		int location_numberOfRows;

	};

}