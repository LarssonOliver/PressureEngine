#include "ShadowShader.h"
#include "ShadowShaderSource.h"

namespace Pressure {

	ShadowShader::ShadowShader() {
		ShaderProgram::loadShaders(ShadowShaderSource::vertexShader, ShadowShaderSource::fragmentShader);
	}

	void ShadowShader::getAllUniformLocations() {
		location_mvpMatrix = ShaderProgram::getUniformLocation("mvpMatrix");
	}

	void ShadowShader::loadMvpMatrix(Matrix4f& matrix) {
		ShaderProgram::loadMatrix(location_mvpMatrix, matrix);
	}

	void ShadowShader::bindAttributes() {
		ShaderProgram::bindAttribute(0, "in_position");
	}

}