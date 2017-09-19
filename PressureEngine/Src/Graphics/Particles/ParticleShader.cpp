#include "ParticleShader.h"

namespace Pressure {

	const char* ParticleShader::VERTEX_FILE = "src/Graphics/Particles/ParticleVertexShader.glsl";
	const char* ParticleShader::FRAGMENT_FILE = "src/Graphics/Particles/ParticleFragmentShader.glsl";

	void ParticleShader::getAllUniformLocations() {
		location_transformationMatrix = ShaderProgram::getUniformLocation("transformationMatrix");
		location_viewMatrix = ShaderProgram::getUniformLocation("viewMatrix");
	}

	void ParticleShader::bindAttributes() {
		ShaderProgram::bindAttribute(0, "position");
	}

	void ParticleShader::loadTransformationMatrix(Matrix4f& matrix) {
		ShaderProgram::loadMatrix(location_transformationMatrix, matrix);
	}

}