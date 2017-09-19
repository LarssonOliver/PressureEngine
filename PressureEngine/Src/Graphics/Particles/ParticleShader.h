#pragma once
#include "../Shaders/ShaderProgram.h"
#include "../Entities/Camera.h"

namespace Pressure {

	class ParticleShader : public ShaderProgram {

	private:
		static const char* VERTEX_FILE;
		static const char* FRAGMENT_FILE;

	protected:
		virtual void getAllUniformLocations() override;
		virtual void bindAttributes() override;

	public:
		void loadProjectionMatrix(Matrix4f& matrix);
		void loadViewMatrix(Matrix4f& matrix);

	private:
		int location_projectionMatrix;
		int location_viewMatrix;

	};

}