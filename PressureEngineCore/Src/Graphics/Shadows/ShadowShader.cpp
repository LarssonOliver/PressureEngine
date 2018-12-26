#include "ShadowShader.h"
#include "ShadowShaderSource.h"

namespace Pressure {

	ShadowShader::ShadowShader() {
		Shader::loadShaders(ShadowShaderSource::vertexShader, ShadowShaderSource::fragmentShader);
	}

	void ShadowShader::getAllUniformLocations() {
		location_mvpMatrix = Shader::getUniformLocation("mvpMatrix");
	}

	void ShadowShader::loadMvpMatrix(Matrix4f& matrix) {
		Shader::loadMatrix(location_mvpMatrix, matrix);
	}

	void ShadowShader::bindAttributes() {
		Shader::bindAttribute(0, "in_position");
	}

}