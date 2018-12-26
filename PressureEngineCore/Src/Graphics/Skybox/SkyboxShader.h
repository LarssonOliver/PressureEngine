#pragma once
#include "../Shaders/Shader.h"
#include "../Entities/Camera.h"

namespace Pressure {

	class SkyboxShader : public Shader {

	public:
		SkyboxShader();

	protected:
		virtual void bindAttributes() override;
		virtual void getAllUniformLocations() override;

	public:
		void loadProjectionMatrix(Matrix4f& matrix);
		void loadViewMatrix(Camera& camera);

	private:
		int location_projectionMatrix;
		int location_viewMatrix;

	};

}
