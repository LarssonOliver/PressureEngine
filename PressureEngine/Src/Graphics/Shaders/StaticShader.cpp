#include "StaticShader.h"

namespace Pressure {

	StaticShader::StaticShader() {
		ShaderProgram::loadShaders(PRESSURE_ENGINE_STATIC_VERTEX_FILE, PRESSURE_ENGINE_STATIC_FRAGMENT_FILE);
	}

	void StaticShader::bindAttributes() {
		ShaderProgram::bindAttribute(0, "position");
	}

}

