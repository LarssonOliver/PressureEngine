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
	}

	void StaticShader::loadTransformationMatrix(Matrix4f& matrix) {
		ShaderProgram::loadMatrix(location_transformationMatrix, matrix);
	}

}

