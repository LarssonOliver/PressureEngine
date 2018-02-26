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

uniform vec2 targetSize;
uniform float focus;

const float near = 0.1;
const float far = 1000.0;
const float imageDistance = 0.5;
const float maxBlur = 3.0;

vec4 horizontalBlur(vec4 color, float pixelWidth, float samples) {
	float sigma = samples / 2.5;
}

void main(void) {
	
	float aperture = focus / 2;
	float depth = texture(depthTexture, textureCoords).r;
	float objectDistance = -far * near / (depth * (far - near) - far);
	float focalLength = 1 / (1 / focus + 1 / imageDistance);
	float CoC = abs(aperture * (focalLength * (objectDistance - focus)) / (objectDistance * (focus - focalLength)));
    CoC = min(CoC, maxBlur);     
		
	out_Color = texture(colorTexture, textureCoords);
	out_Color = vec4(CoC);

})";

	DepthOfFieldShader::DepthOfFieldShader() {
		ShaderProgram::loadShaders(s_VertexShader, s_FragmentShader);
	}

	void DepthOfFieldShader::getAllUniformLocations() {
		location_colorTexture = ShaderProgram::getUniformLocation("colorTexture");
		location_depthTexture = ShaderProgram::getUniformLocation("depthTexture");
		location_focus = ShaderProgram::getUniformLocation("focus");
		location_targetSize = ShaderProgram::getUniformLocation("targetSize");
	}

	void DepthOfFieldShader::bindAttributes() {
		ShaderProgram::bindAttribute(0, "position");
	}

	void DepthOfFieldShader::connectTextureUnits() {
		ShaderProgram::loadInt(location_colorTexture, 0);
		ShaderProgram::loadInt(location_depthTexture, 1);
	}

	void DepthOfFieldShader::loadFocus(float focus) {
		ShaderProgram::loadFloat(location_focus, focus);
	}

	void DepthOfFieldShader::loadTargetSize(Vector2f& targetSize) {
		ShaderProgram::loadVector(targetSize);
	}

}