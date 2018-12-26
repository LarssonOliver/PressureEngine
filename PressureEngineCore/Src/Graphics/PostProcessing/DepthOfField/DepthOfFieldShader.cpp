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

const float near = 0.1;
const float far = 1000.0;
const float imageDistance = 0.5;
const float maxBlur = 1.0;

const float sqrt2pi = sqrt(2 * 3.1415926); // Used in deviation().

float deviation(float sigma, float x) {
	return 1 / (sigma * sqrt2pi) * exp(-0.5 * pow(x / sigma, 2));	
}

vec4 verticalBlur(float pixelHeight, float samples) { // samples has to be an odd number.
	float sigma = samples / 2.5;
	float minmax = (samples - 1) / 2;
	
	vec4 result = vec4(0.0);
	vec2 blurCoords = textureCoords;
	blurCoords.y -= minmax * pixelHeight;
	float totalDeviation = 0.0;
	for (float i = -minmax; i <= minmax; i++) {
		float dev = deviation(sigma, i);
		totalDeviation += dev;
		result += texture(colorTexture, clamp(blurCoords, 0.0, 1.0)) * dev;
		blurCoords.y += pixelHeight;
	}
	result /= totalDeviation;
	result.a = 1.0;
	return result;
}

vec4 horizontalBlur(float pixelWidth, float samples) { // samples has to be an odd number.
	float sigma = samples / 2.5;
	float minmax = (samples - 1) / 2;
	
	vec4 result = vec4(0.0);
	vec2 blurCoords = textureCoords;
	blurCoords.x -= minmax * pixelWidth;
	float totalDeviation = 0.0;
	for (float i = -minmax; i <= minmax; i++) {
		float dev = deviation(sigma, i);
		totalDeviation += dev;
		result += texture(colorTexture, clamp(blurCoords, 0.0, 1.0)) * dev;
		blurCoords.x += pixelWidth;
	}
	result /= totalDeviation;
	result.a = 1.0;
	return result;
}

void main(void) {
	float focus = texture(depthTexture, vec2(0.5)).r;
	focus += texture(depthTexture, vec2(0.51)).r;
	focus += texture(depthTexture, vec2(0.49)).r;
	focus += texture(depthTexture, vec2(0.51, 0.49)).r;
	focus += texture(depthTexture, vec2(0.49, 0.51)).r;
	focus /= 5;
	float focusPlane = 2.0 * near * far / (near + far - (2.0 * focus - 1.0) * (far - near));
	if (focusPlane > 100) {
		focusPlane = 40;
	}

	float aperture = max(focusPlane / 2, 1.0);
	float depth = texture(depthTexture, textureCoords).r;
	float objectDistance = -far * near / (depth * (far - near) - far);
	float focalLength = 1 / (1 / focusPlane + 1 / imageDistance);
	float CoC = abs(aperture * (focalLength * (objectDistance - focusPlane)) / (objectDistance * (focusPlane - focalLength)));
    CoC = min(CoC, maxBlur);     
	
	float samples = floor(CoC * 15 + 0.5) * 2 + 1;
	if (samples > 1.0) {
		out_Color = (horizontalBlur(1 / targetSize.x, samples) + verticalBlur(1 / targetSize.y, samples)) / 2;
	} else {
		out_Color = texture(colorTexture, textureCoords);
	}

})";

	DepthOfFieldShader::DepthOfFieldShader() {
		Shader::loadShaders(s_VertexShader, s_FragmentShader);
	}

	void DepthOfFieldShader::getAllUniformLocations() {
		location_colorTexture = Shader::getUniformLocation("colorTexture");
		location_depthTexture = Shader::getUniformLocation("depthTexture");
		location_targetSize = Shader::getUniformLocation("targetSize");
	}

	void DepthOfFieldShader::bindAttributes() {
		Shader::bindAttribute(0, "position");
	}

	void DepthOfFieldShader::connectTextureUnits() {
		Shader::loadInt(location_colorTexture, 0);
		Shader::loadInt(location_depthTexture, 1);
	}

	void DepthOfFieldShader::loadTargetSize(Vector2f& targetSize) {
		Shader::loadVector(location_targetSize, targetSize);
	}

}