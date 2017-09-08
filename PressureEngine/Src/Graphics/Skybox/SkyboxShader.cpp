#include "SkyboxShader.h"

namespace Pressure {

	SkyboxShader::SkyboxShader() {
		ShaderProgram::loadShaders(PRESSURE_ENGINE_SKYBOX_VERTEX_FILE, PRESSURE_ENGINE_SKYBOX_FRAGMENT_FILE);
	}

	void SkyboxShader::bindAttributes() {
		ShaderProgram::bindAttribute(0, "position");
	}

	void SkyboxShader::getAllUniformLocations() {
		location_projectionMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
		location_viewMatrix = ShaderProgram::getUniformLocation("viewMatrix");
	}

	void SkyboxShader::loadProjectionMatrix(Matrix4f& matrix) {
		ShaderProgram::loadMatrix(location_projectionMatrix, matrix);
	}

	void SkyboxShader::loadViewMatrix(Camera& camera) {
		ShaderProgram::loadMatrix(location_viewMatrix, Matrix4f().createViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw(), camera.getRoll()));
	}

}
