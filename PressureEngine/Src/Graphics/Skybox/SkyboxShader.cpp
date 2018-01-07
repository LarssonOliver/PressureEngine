#include "SkyboxShader.h"
#include "SkyboxShaderSource.h"

namespace Pressure {

	SkyboxShader::SkyboxShader() {
		ShaderProgram::loadShaders(SkyboxShaderSource::vertexShader, SkyboxShaderSource::fragmentShader);
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
		Matrix4f matrix = Matrix4f().createViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw(), camera.getRoll());
		matrix.set(3, 0, 0);
		matrix.set(3, 1, 0);
		matrix.set(3, 2, 0);
		ShaderProgram::loadMatrix(location_viewMatrix, matrix);
	}

}
