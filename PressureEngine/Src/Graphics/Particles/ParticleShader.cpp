#include "ParticleShader.h"
#include "ParticleShaderSource.h"

namespace Pressure {

	ParticleShader::ParticleShader() {
		ShaderProgram::loadShaders(ParticleShaderSource::vertexShader, ParticleShaderSource::fragmentShader);
	}

	void ParticleShader::getAllUniformLocations() {
		location_projectionMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
		location_numberOfRows = ShaderProgram::getUniformLocation("numberOfRows");
	}

	void ParticleShader::bindAttributes() {
		ShaderProgram::bindAttribute(0, "position");
		ShaderProgram::bindAttribute(1, "viewMatrix");
		ShaderProgram::bindAttribute(5, "texOffsets");
		ShaderProgram::bindAttribute(6, "blendFactor");

	}

	void ParticleShader::loadProjectionMatrix(Matrix4f& matrix) {
		ShaderProgram::loadMatrix(location_projectionMatrix, matrix);
	}

	void ParticleShader::loadNumberOfRows(const float numberOfRows) {
		ShaderProgram::loadFloat(location_numberOfRows, numberOfRows);
	}

}