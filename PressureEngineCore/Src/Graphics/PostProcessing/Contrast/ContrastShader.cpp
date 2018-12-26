#include "ContrastShader.h"

namespace Pressure {

	const std::string ContrastShader::s_VertexShader =
R"(#version 140

in vec2 position;

out vec2 textureCoords;

void main(void) {

	gl_Position = vec4(position, 0.0, 1.0);
	textureCoords = position * 0.5 + 0.5;
	
})";

	const std::string ContrastShader::s_FragmentShader =
R"(#version 140

in vec2 textureCoords;

out vec4 out_Color;

uniform sampler2D colorTexture;

const float contrast = 0.15;

void main(void) {

	out_Color = texture(colorTexture, textureCoords);
	out_Color.rgb = (out_Color.rgb - 0.5) * (1.0 + contrast) + 0.5;

})";

	ContrastShader::ContrastShader() {	
		Shader::loadShaders(s_VertexShader, s_FragmentShader);
	}

	void ContrastShader::bindAttributes() {
		Shader::bindAttribute(0, "position");
	}

}