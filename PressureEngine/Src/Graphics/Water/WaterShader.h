#pragma once
#include "../Shaders/ShaderProgram.h"
#include "../Entities/Camera.h"

namespace Pressure{

	class WaterShader : public ShaderProgram {

#define PRESSURE_ENGINE_WATER_VERTEX_FILE "Src/Graphics/Water/WaterVertexShader.glsl"
#define PRESSURE_ENGINE_WATER_FRAGMENT_FILE "Src/Graphics/Water/WaterFragmentShader.glsl"

	public:
		WaterShader();

	protected:
		virtual void bindAttributes() override;
		virtual void getAllUniformLocations() override;

	public:
		void loadTransformationMatrix(Matrix4f& matrix);
		void loadProjectionMatrix(Matrix4f& matrix);
		void loadViewMatrix(Camera& camera);
		void loadWaveModifier(float angle);

	private:
		int location_transformationMatrix;
		int location_projectionMatrix;
		int location_viewMatrix;
		int location_waveModifier;

	};

}