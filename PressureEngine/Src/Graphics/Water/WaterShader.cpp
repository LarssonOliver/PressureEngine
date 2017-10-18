#include "WaterShader.h"

namespace Pressure {

	WaterShader::WaterShader() {
		ShaderProgram::loadShaders(PRESSURE_ENGINE_WATER_VERTEX_FILE, PRESSURE_ENGINE_WATER_FRAGMENT_FILE);
	}

	void WaterShader::bindAttributes() {
		ShaderProgram::bindAttribute(0, "position");
	}

	void WaterShader::getAllUniformLocations() {
		location_transformationMatrix = ShaderProgram::getUniformLocation("transformationMatrix");
		location_projectionMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
		location_viewMatrix = ShaderProgram::getUniformLocation("viewMatrix");
		location_waveModifier = ShaderProgram::getUniformLocation("waveModifier");
		location_reflectionTexture = ShaderProgram::getUniformLocation("reflectionTexture");
		location_refractionTexture = ShaderProgram::getUniformLocation("refractionTexture");
		location_depthMap = ShaderProgram::getUniformLocation("depthMap");

		for (int i = 0; i < 4; i++) {
			location_lightColor[i] = ShaderProgram::getUniformLocation(("lightColor[" + std::to_string(i) + "]").c_str());
			location_lightPosition[i] = ShaderProgram::getUniformLocation(("lightPosition[" + std::to_string(i) + "]").c_str());
			location_attenuation[i] = ShaderProgram::getUniformLocation(("attenuation[" + std::to_string(i) + "]").c_str());
		}
	}

	void WaterShader::loadTransformationMatrix(Matrix4f& matrix) {
		ShaderProgram::loadMatrix(location_transformationMatrix, matrix);
	}

	void WaterShader::loadProjectionMatrix(Matrix4f& matrix) {
		ShaderProgram::loadMatrix(location_projectionMatrix, matrix);
	}

	void WaterShader::loadViewMatrix(Camera& camera) {
		ShaderProgram::loadMatrix(location_viewMatrix, Matrix4f().createViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw(), camera.getRoll()));
	}

	void WaterShader::loadWaveModifier(float angle) {
		ShaderProgram::loadFloat(location_waveModifier, angle);
	}

	void WaterShader::loadLights(std::vector<Light>& lights) {
		for (int i = 0; i < 4; i++) {
			if (i < lights.size()) {
				ShaderProgram::loadVector(location_lightPosition[i], lights[i].getPosition());
				ShaderProgram::loadVector(location_lightColor[i], lights[i].getColor());
				ShaderProgram::loadVector(location_attenuation[i], lights[i].getAttenuation());
			}
			else {
				ShaderProgram::loadVector(location_lightPosition[i], Vector3f(0));
				ShaderProgram::loadVector(location_lightColor[i], Vector3f(0));
				ShaderProgram::loadVector(location_attenuation[i], Vector3f(1, 0, 0));
			}
		}
	}

	void WaterShader::connectTextureUnits() {
		ShaderProgram::loadInt(location_reflectionTexture, 0);
		ShaderProgram::loadInt(location_refractionTexture, 1);
		ShaderProgram::loadInt(location_depthMap, 2);
	}

}
