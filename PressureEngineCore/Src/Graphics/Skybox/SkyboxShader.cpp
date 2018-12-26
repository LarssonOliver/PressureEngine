#include "SkyboxShader.h"
#include "SkyboxShaderSource.h"

namespace Pressure {

	SkyboxShader::SkyboxShader() {
		Shader::loadShaders(SkyboxShaderSource::vertexShader, SkyboxShaderSource::fragmentShader);
	}

	void SkyboxShader::bindAttributes() {
		Shader::bindAttribute(0, "position");
	}

	void SkyboxShader::getAllUniformLocations() {
		location_projectionMatrix = Shader::getUniformLocation("projectionMatrix");
		location_viewMatrix = Shader::getUniformLocation("viewMatrix");
	}

	void SkyboxShader::loadProjectionMatrix(Matrix4f& matrix) {
		Shader::loadMatrix(location_projectionMatrix, matrix);
	}

	void SkyboxShader::loadViewMatrix(Camera& camera) {
		Matrix4f matrix = Matrix4f().createViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw(), camera.getRoll());
		matrix.set(3, 0, 0);
		matrix.set(3, 1, 0);
		matrix.set(3, 2, 0);
		Shader::loadMatrix(location_viewMatrix, matrix);
	}

}
