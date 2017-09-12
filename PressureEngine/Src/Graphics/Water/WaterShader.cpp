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

}
