#pragma once
#include "ShaderProgram.h"
#include "../Entities/Camera.h"
#include "../Entities/Light.h"

namespace Pressure {

	class StaticShader : public ShaderProgram {

#define PRESSURE_ENGINE_STATIC_VERTEX_FILE "Src/Graphics/Shaders/VertexShader.glsl"
#define PRESSURE_ENGINE_STATIC_FRAGMENT_FILE "Src/Graphics/Shaders/FragmentShader.glsl"

	public:
		StaticShader();

	protected:
		virtual void bindAttributes() override;
		virtual void getAllUniformLocations() override;

	public:
		//load uniforms.
		void loadTransformationMatrix(Matrix4f& matrix);
		void loadProjectionmatrix(Matrix4f& matrix);
		void loadViewMatrix(Camera& camera);
		void loadLight(Light& light);
		void loadShineVariables(float damper, float reflectivity);
		void loadFakeLighting(bool useFakeLighting);

	private:
		//uniform locations.
		int location_transformationMatrix;
		int location_projectionMatrix;
		int location_viewMatrix;
		int location_lightPosition;
		int location_lightColor;
		int location_shineDamper;
		int location_reflectivity;
		int location_fakeLighting;

	};

}
