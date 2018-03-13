#include "WaterShader.h"
#include "WaterShaderSource.h"

namespace Pressure {

	WaterShader::WaterShader() {
		Shader::loadShaders(WaterShaderSource::vertexShader, WaterShaderSource::fragmentShader);
	}

	void WaterShader::bindAttributes() {
		Shader::bindAttribute(0, "position");
	}

	void WaterShader::getAllUniformLocations() {
		location_transformationMatrix = Shader::getUniformLocation("transformationMatrix");
		location_projectionMatrix = Shader::getUniformLocation("projectionMatrix");
		location_viewMatrix = Shader::getUniformLocation("viewMatrix");
		location_waveModifier = Shader::getUniformLocation("waveModifier");
		location_reflectionTexture = Shader::getUniformLocation("reflectionTexture");
		location_refractionTexture = Shader::getUniformLocation("refractionTexture");
		location_depthMap = Shader::getUniformLocation("depthMap");

		for (int i = 0; i < 4; i++) {
			location_lightColor[i] = Shader::getUniformLocation(("lightColor[" + std::to_string(i) + "]").c_str());
			location_lightPosition[i] = Shader::getUniformLocation(("lightPosition[" + std::to_string(i) + "]").c_str());
			location_attenuation[i] = Shader::getUniformLocation(("attenuation[" + std::to_string(i) + "]").c_str());
		}
	}

	void WaterShader::loadTransformationMatrix(Matrix4f& matrix) {
		Shader::loadMatrix(location_transformationMatrix, matrix);
	}

	void WaterShader::loadProjectionMatrix(Matrix4f& matrix) {
		Shader::loadMatrix(location_projectionMatrix, matrix);
	}

	void WaterShader::loadViewMatrix(Camera& camera) {
		Shader::loadMatrix(location_viewMatrix, Matrix4f().createViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw(), camera.getRoll()));
	}

	void WaterShader::loadWaveModifier(float angle) {
		Shader::loadFloat(location_waveModifier, angle);
	}

	void WaterShader::loadLights(std::vector<Light>& lights) {
		for (unsigned int i = 0; i < 4; i++) {
			if (i < lights.size()) {
				Shader::loadVector(location_lightPosition[i], lights[i].getPosition());
				Shader::loadVector(location_lightColor[i], lights[i].getColor());
				Shader::loadVector(location_attenuation[i], lights[i].getAttenuation());
			}
			else {
				Shader::loadVector(location_lightPosition[i], Vector3f(0));
				Shader::loadVector(location_lightColor[i], Vector3f(0));
				Shader::loadVector(location_attenuation[i], Vector3f(1, 0, 0));
			}
		}
	}

	void WaterShader::connectTextureUnits() {
		Shader::loadInt(location_reflectionTexture, 0);
		Shader::loadInt(location_refractionTexture, 1);
		Shader::loadInt(location_depthMap, 2);
	}

}
