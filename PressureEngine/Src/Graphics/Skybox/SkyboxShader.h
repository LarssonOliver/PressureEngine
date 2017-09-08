#pragma once
#include "../Shaders/ShaderProgram.h"
#include "../Entities/Camera.h"

namespace Pressure {

	class SkyboxShader : public ShaderProgram {

#define PRESSURE_ENGINE_SKYBOX_VERTEX_FILE "Src/Graphics/Skybox/SkyboxVertexShader.glsl"
#define PRESSURE_ENGINE_SKYBOX_FRAGMENT_FILE "Src/Graphics/Skybox/SkyboxFragmentShader.glsl"

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
