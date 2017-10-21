#include "ShadowShader.h"

namespace Pressure {

	const char* ShadowShader::VERTEX_FILE = "Src/Graphics/Shadows/ShadowVertexShader.glsl";
	const char* ShadowShader::FRAGMENT_FILE = "Src/Graphics/Shadows/ShadowFragmentShader.glsl";

	ShadowShader::ShadowShader() {
		ShaderProgram::loadShaders(VERTEX_FILE, FRAGMENT_FILE);
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