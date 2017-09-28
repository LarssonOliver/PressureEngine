#pragma once
#include "../Shaders/ShaderProgram.h"

namespace Pressure {

	class ParticleShader : public ShaderProgram {

	private:
		static const char* VERTEX_FILE;
		static const char* FRAGMENT_FILE;

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