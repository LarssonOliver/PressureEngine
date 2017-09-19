#include "ParticleShader.h"

namespace Pressure {

	const char* ParticleShader::VERTEX_FILE = "src/Graphics/Particles/ParticleVertexShader.glsl";
	const char* ParticleShader::FRAGMENT_FILE = "src/Graphics/Particles/ParticleFragmentShader.glsl";

	void ParticleShader::getAllUniformLocations() {
		location_projectionMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
		location_viewMatrix = ShaderProgram::getUniformLocation("viewMatrix");
	}

	void ParticleShader::bindAttributes() {
		ShaderProgram::bindAttribute(0, "position");
	}

	void ParticleShader::loadProjectionMatrix(Matrix4f& matrix) {
		ShaderProgram::loadMatrix(location_projectionMatrix, matrix);
	}

	void ParticleShader::loadViewMatrix(Matrix4f& matrix) {
		ShaderProgram::loadMatrix(location_viewMatrix, matrix);
	}

}