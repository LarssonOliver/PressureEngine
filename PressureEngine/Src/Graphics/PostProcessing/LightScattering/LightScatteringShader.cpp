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
uniform vec2 lightPositionOnScreen;

const float exposure = 0.2;
const float decay = 0.95;
const float density = 2;
const float weight = 0.2;

const int NUM_SAMPLES = 100;

void main()
{	

    vec2 deltaTextCoord = textureCoords - lightPositionOnScreen;
    vec2 textCoo = textureCoords;
    deltaTextCoord *= 1.0 /  float(NUM_SAMPLES) * density;
    float illuminationDecay = 1.0;
	
	
    for(int i=0; i < NUM_SAMPLES ; i++)
    {
        textCoo -= deltaTextCoord;
        vec4 sample = texture2D(lightTexture, textCoo);
			
        sample *= illuminationDecay * weight;

        out_Color += sample;

        illuminationDecay *= decay;
    }
    out_Color *= exposure;

})";

	LightScatteringShader::LightScatteringShader() {
		ShaderProgram::loadShaders(s_VertexShader, s_FragmentShader);
	}

	void LightScatteringShader::getAllUniformLocations() {
		location_lightPositionOnScreen = ShaderProgram::getUniformLocation("lightPositionOnScreen");
	}

	void LightScatteringShader::bindAttributes() {
		ShaderProgram::bindAttribute(0, "position");
	}

	void LightScatteringShader::loadLightPosition(Vector2f& lightPosition) {
		ShaderProgram::loadVector(location_lightPositionOnScreen, lightPosition);
	}

}