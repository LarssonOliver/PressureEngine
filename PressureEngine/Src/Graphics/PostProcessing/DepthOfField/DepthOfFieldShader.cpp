#include "DepthOfFieldShader.h"

namespace Pressure {

	const std::string DepthOfFieldShader::s_VertexShader =
R"(#version 140

in vec2 position;

out vec2 textureCoords;

void main(void) {

	gl_Position = vec4(position, 0.0, 1.0);
	textureCoords = position * 0.5 + 0.5;
	
})";

	const std::string DepthOfFieldShader::s_FragmentShader =
R"(#version 140

in vec2 textureCoords;

out vec4 out_Color;

uniform sampler2D colorTexture;
uniform sampler2D depthTexture;

const float near = 0.1;
const float far = 1000.0;
const float aperture = 1.0;
const float focus = 5.0;
const float imageDistance = 0.5;

void main(void) {

	float depth = texture(depthTexture, textureCoords).r;
	float objectDistance = -far * near / (depth * (far - near) - far);
	float focalLength = 1 / (1 / focus + 1 / imageDistance);
	float CoC = abs(aperture * (focalLength * (objectDistance - focus)) / (objectDistance * (focus - focalLength)));

	out_Color = texture(colorTexture, textureCoords);
	out_Color = vec4(CoC);

})";

	DepthOfFieldShader::DepthOfFieldShader() {
		ShaderProgram::loadShaders(s_VertexShader, s_FragmentShader);
	}

	void DepthOfFieldShader::getAllUniformLocations() {
		location_colorTexture = ShaderProgram::getUniformLocation("colorTexture");
		location_depthTexture = ShaderProgram::getUniformLocation("depthTexture");
	}

	void DepthOfFieldShader::bindAttributes() {
		ShaderProgram::bindAttribute(0, "position");
	}

	void DepthOfFieldShader::connectTextureUnits() {
		ShaderProgram::loadInt(location_colorTexture, 0);
		ShaderProgram::loadInt(location_depthTexture, 1);
	}

}