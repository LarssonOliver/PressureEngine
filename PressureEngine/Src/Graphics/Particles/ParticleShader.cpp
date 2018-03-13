#include "ParticleShader.h"
#include "ParticleShaderSource.h"

namespace Pressure {

	ParticleShader::ParticleShader() {
		Shader::loadShaders(ParticleShaderSource::vertexShader, ParticleShaderSource::fragmentShader);
	}

	void ParticleShader::getAllUniformLocations() {
		location_projectionMatrix = Shader::getUniformLocation("projectionMatrix");
		location_numberOfRows = Shader::getUniformLocation("numberOfRows");
	}

	void ParticleShader::bindAttributes() {
		Shader::bindAttribute(0, "position");
		Shader::bindAttribute(1, "viewMatrix");
		Shader::bindAttribute(5, "texOffsets");
		Shader::bindAttribute(6, "blendFactor");

	}

	void ParticleShader::loadProjectionMatrix(Matrix4f& matrix) {
		Shader::loadMatrix(location_projectionMatrix, matrix);
	}

	void ParticleShader::loadNumberOfRows(const float numberOfRows) {
		Shader::loadFloat(location_numberOfRows, numberOfRows);
	}

}