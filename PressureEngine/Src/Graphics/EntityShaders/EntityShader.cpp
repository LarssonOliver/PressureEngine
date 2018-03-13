#include "EntityShader.h"
#include "EntityShaderSource.h"

namespace Pressure {

	EntityShader::EntityShader() {
		Shader::loadShaders(EntityShaderSource::vertexShader, EntityShaderSource::geometryShader, EntityShaderSource::fragmentShader);
	}

	void EntityShader::bindAttributes() {
		Shader::bindAttribute(0, "position");
		Shader::bindAttribute(1, "textureCoords");
		Shader::bindAttribute(2, "normal");
	}

	void EntityShader::getAllUniformLocations() {
		location_transformationMatrix = Shader::getUniformLocation("transformationMatrix");
		location_projectionMatrix = Shader::getUniformLocation("projectionMatrix");
		location_viewMatrix = Shader::getUniformLocation("viewMatrix");
		location_shineDamper = Shader::getUniformLocation("shineDamper");
		location_reflectivity = Shader::getUniformLocation("reflectivity");
		location_fakeLighting = Shader::getUniformLocation("fakeLighting");
		location_plane = Shader::getUniformLocation("plane");
		location_toShadowMapSpace = Shader::getUniformLocation("toShadowMapSpace");
		location_shadowMap = Shader::getUniformLocation("shadowMap");
		location_textureSampler = Shader::getUniformLocation("textureSampler");
		location_windModifier = Shader::getUniformLocation("windModifier");
		location_shadowDistance = Shader::getUniformLocation("shadowDistance");

		for (int i = 0; i < 4; i++) {
			location_lightColor[i] = Shader::getUniformLocation(("lightColor[" + std::to_string(i) + "]").c_str());
			location_lightPosition[i] = Shader::getUniformLocation(("lightPosition[" + std::to_string(i) + "]").c_str());
			location_attenuation[i] = Shader::getUniformLocation(("attenuation[" + std::to_string(i) + "]").c_str());
		}
	}

	void EntityShader::loadTransformationMatrix(Matrix4f& matrix) {
		Shader::loadMatrix(location_transformationMatrix, matrix);
	}

	void EntityShader::loadProjectionmatrix(Matrix4f& matrix) {
		Shader::loadMatrix(location_projectionMatrix, matrix);
	}

	void EntityShader::loadViewMatrix(Matrix4f& matrix) {
		Shader::loadMatrix(location_viewMatrix, matrix);
	}

	void EntityShader::loadLights(std::vector<Light>& lights) {
		for (unsigned int i = 0; i < 4; i++) {
			if (i < lights.size()) {
				Shader::loadVector(location_lightPosition[i], lights[i].getPosition());
				Shader::loadVector(location_lightColor[i], lights[i].getColor());	
				Shader::loadVector(location_attenuation[i], lights[i].getAttenuation());
			} else {
				Shader::loadVector(location_lightPosition[i], Vector3f(0));
				Shader::loadVector(location_lightColor[i], Vector3f(0));
				Shader::loadVector(location_attenuation[i], Vector3f(1, 0, 0));
			}
		}
	}

	void EntityShader::loadShineVariables(float damper, float reflectivity) {
		Shader::loadFloat(location_shineDamper, damper);
		Shader::loadFloat(location_reflectivity, reflectivity);
	}

	void EntityShader::loadFakeLighting(bool useFakeLighting) {
		Shader::loadBool(location_fakeLighting, useFakeLighting);
	}

	void EntityShader::loadClipPlane(const Vector4f& plane) {
		Shader::loadVector(location_plane, plane);
	}

	void EntityShader::loadToShadowMapSpace(Matrix4f& matrix) {
		Shader::loadMatrix(location_toShadowMapSpace, matrix);
	}

	void EntityShader::connectTextureUnits() {
		Shader::loadInt(location_textureSampler, 0);
		Shader::loadInt(location_shadowMap, 1);
	}

	void EntityShader::loadWindModifier(const float windModifier) {
		Shader::loadFloat(location_windModifier, windModifier);
	}

	void EntityShader::loadShadowDistance(float shadowDistance) {
		Shader::loadFloat(location_shadowDistance, shadowDistance);
	}

}