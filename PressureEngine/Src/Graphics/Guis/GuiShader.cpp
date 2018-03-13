#include "GuiShader.h"
#include "GuiShaderSource.h"

namespace Pressure {

	GuiShader::GuiShader() {
		Shader::loadShaders(GuiShaderSource::vertexShader, GuiShaderSource::fragmentShader);
	}

	void GuiShader::loadTransformation(Matrix4f& matrix) {
		Shader::loadMatrix(location_transformationMatrix, matrix);
	}

	void GuiShader::getAllUniformLocations() {
		location_transformationMatrix = Shader::getUniformLocation("transformationMatrix");
	}

	void GuiShader::bindAttributes() {
		Shader::bindAttribute(0, "position");
	}

}
