#include "StaticShader.h"

namespace Pressure {

	StaticShader::StaticShader() {
		ShaderProgram::loadShaders(PRESSURE_ENGINE_STATIC_VERTEX_FILE, PRESSURE_ENGINE_STATIC_FRAGMENT_FILE);
	}

	void StaticShader::bindAttributes() {
		ShaderProgram::bindAttribute(0, "position");
		ShaderProgram::bindAttribute(1, "textureCoords");
	}

	void StaticShader::getAllUniformLocations() {
		location_transformationMatrix = ShaderProgram::getUniformLocation("transformationMatrix");
		location_projectionMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
		location_viewMatrix = ShaderProgram::getUniformLocation("viewMatrix");
	}

	void StaticShader::loadTransformationMatrix(Matrix4f& matrix) {
		ShaderProgram::loadMatrix(location_transformationMatrix, matrix);
	}

	void StaticShader::loadProjectionmatrix(Matrix4f& matrix) {
		ShaderProgram::loadMatrix(location_projectionMatrix, matrix);
	}

	void StaticShader::loadViewMatrix(Camera& camera) {
		ShaderProgram::loadMatrix(location_viewMatrix, Matrix4f().createViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw(), camera.getRoll()));
	}

}