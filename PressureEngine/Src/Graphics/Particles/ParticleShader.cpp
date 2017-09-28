#include "ParticleShader.h"

namespace Pressure {

	const char* ParticleShader::VERTEX_FILE = "src/Graphics/Particles/ParticleVertexShader.glsl";
	const char* ParticleShader::FRAGMENT_FILE = "src/Graphics/Particles/ParticleFragmentShader.glsl";

	ParticleShader::ParticleShader() {
		ShaderProgram::loadShaders(VERTEX_FILE, FRAGMENT_FILE);
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