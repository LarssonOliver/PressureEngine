#include "LightScatteringShader.h"

namespace Pressure {

	const std::string LightScatteringShader::s_VertexShader =
R"(#version 140

in vec2 position;

out vec2 textureCoords;

void main(void) {

	gl_Position = vec4(position, 0.0, 1.0);
	textureCoords = position * 0.5 + 0.5;
	
})";

	const std::string LightScatteringShader::s_FragmentShader =
R"(#version 140

in vec2 textureCoords;

out vec4 out_Color;

uniform sampler2D lightTexture;
uniform sampler2D colorTexture;
uniform vec2 lightPositionOnScreen;

const float exposure = 0.0034;
const float decay = 1.0;
const float density = 0.84;
const float weight = 5.65;

const int NUM_SAMPLES = 100;

const vec2 outsideScreen = vec2(100.0, 0.0);

void main()
{	
	if (lightPositionOnScreen != outsideScreen) {
		vec4 lightColor;
		vec2 deltaTextCoord = textureCoords - lightPositionOnScreen;
		vec2 textCoo = textureCoords;
		deltaTextCoord *= 1.0 /  float(NUM_SAMPLES) * density;
		float illuminationDecay = 1.0;
	
		for(int i=0; i < NUM_SAMPLES ; i++)
		{
			textCoo -= deltaTextCoord;
			vec4 sample = texture2D(lightTexture, textCoo);
			
			sample *= illuminationDecay * weight;

			lightColor += sample;

			illuminationDecay *= decay;
		}

		lightColor *= exposure;
		out_Color = texture(colorTexture, textureCoords);

		vec2 blendFactor = lightPositionOnScreen;
		blendFactor *= 2.0;
		blendFactor -= 1.0;
		blendFactor = sqrt(blendFactor * blendFactor);
		blendFactor = clamp(blendFactor, 0.0, 1.0);
		
		float blend = (blendFactor.x + blendFactor.y) / 2;
		blend = 1 - blend;
		
		out_Color += lightColor * blend;
	} else {		
		out_Color = texture(colorTexture, textureCoords);		
	}

})";

	LightScatteringShader::LightScatteringShader() {
		ShaderProgram::loadShaders(s_VertexShader, s_FragmentShader);
	}

	void LightScatteringShader::getAllUniformLocations() {
		location_lightPositionOnScreen = ShaderProgram::getUniformLocation("lightPositionOnScreen");
		location_lightTexture = ShaderProgram::getUniformLocation("lightTexture");
		location_colorTexture = ShaderProgram::getUniformLocation("colorTexture");
	}

	void LightScatteringShader::bindAttributes() {
		ShaderProgram::bindAttribute(0, "position");
	}

	void LightScatteringShader::connectTextureUnits() {
		ShaderProgram::loadInt(location_lightTexture, 0);
		ShaderProgram::loadInt(location_colorTexture, 1);
	}

	void LightScatteringShader::loadLightPosition(Vector2f& lightPosition) {
		ShaderProgram::loadVector(location_lightPositionOnScreen, lightPosition);
	}

}