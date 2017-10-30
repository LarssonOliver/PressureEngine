#include "GuiShader.h"

namespace Pressure {

	const char* GuiShader::VERTEX_FILE = "Src/Graphics/Guis/GuiVertexShader.glsl";
	const char* GuiShader::FRAGMENT_FILE = "Src/Graphics/Guis/GuiFragmentShader.glsl";

	GuiShader::GuiShader() {
		ShaderProgram::loadShaders(VERTEX_FILE, FRAGMENT_FILE);
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
