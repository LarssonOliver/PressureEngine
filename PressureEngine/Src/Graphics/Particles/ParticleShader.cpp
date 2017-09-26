#include "ParticleShader.h"

namespace Pressure {

	const char* ParticleShader::VERTEX_FILE = "src/Graphics/Particles/ParticleVertexShader.glsl";
	const char* ParticleShader::FRAGMENT_FILE = "src/Graphics/Particles/ParticleFragmentShader.glsl";

	ParticleShader::ParticleShader() {
		ShaderProgram::loadShaders(VERTEX_FILE, FRAGMENT_FILE);
	}

	void ParticleShader::getAllUniformLocations() {
		location_projectionMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
		location_viewMatrix = ShaderProgram::getUniformLocation("viewMatrix");
		location_texOffset1 = ShaderProgram::getUniformLocation("texOffset1");
		location_texOffset2 = ShaderProgram::getUniformLocation("texOffset2");
		location_texCoordInfo = ShaderProgram::getUniformLocation("texCoordInfo");
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

	void ParticleShader::loadTextureCoordInfo(Vector2f& offset1, Vector2f& offset2, float numRows, float blend) {
		ShaderProgram::loadVector(location_texOffset1, offset1);
		ShaderProgram::loadVector(location_texOffset2, offset2);
		ShaderProgram::loadVector(location_texCoordInfo, Vector2f(numRows, blend));
	}

}