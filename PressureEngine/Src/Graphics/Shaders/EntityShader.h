#pragma once
#include "ShaderProgram.h"
#include "../Entities/Camera.h"
#include "../Entities/Light.h"

namespace Pressure {

	class EntityShader : public ShaderProgram {

	public:
		EntityShader();

	protected:
		virtual void bindAttributes() override;
		virtual void getAllUniformLocations() override;

	public:
		//load uniforms.
		void loadTransformationMatrix(Matrix4f& matrix);
		void loadProjectionmatrix(Matrix4f& matrix);
		void loadViewMatrix(Camera& camera);
		void loadLights(std::vector<Light>& lights);
		void loadShineVariables(float damper, float reflectivity);
		void loadFakeLighting(bool useFakeLighting);
		void loadClipPlane(const Vector4f& plane);
		void loadToShadowMapSpace(Matrix4f& matrix);
		void connectTextureUnits();

	private:
		//uniform locations.
		int location_transformationMatrix;
		int location_projectionMatrix;
		int location_viewMatrix;
		int location_lightPosition[4];
		int location_lightColor[4];
		int location_attenuation[4];
		int location_shineDamper;
		int location_reflectivity;
		int location_fakeLighting;
		int location_plane;
		int location_toShadowMapSpace;
		int location_shadowMap;
		int location_textureSampler;

	};

}
