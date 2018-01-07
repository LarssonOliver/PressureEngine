#include "GuiShader.h"
#include "GuiShaderSource.h"

namespace Pressure {

	GuiShader::GuiShader() {
		ShaderProgram::loadShaders(GuiShaderSource::vertexShader, GuiShaderSource::fragmentShader);
	}

	void GuiShader::loadTransformation(Matrix4f& matrix) {
		ShaderProgram::loadMatrix(location_transformationMatrix, matrix);
	}

	void GuiShader::getAllUniformLocations() {
		location_transformationMatrix = ShaderProgram::getUniformLocation("transformationMatrix");
	}

	void GuiShader::bindAttributes() {
		ShaderProgram::bindAttribute(0, "position");
	}

}
