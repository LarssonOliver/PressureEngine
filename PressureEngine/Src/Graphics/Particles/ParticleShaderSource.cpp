#include "ParticleShaderSource.h"

namespace Pressure {
	
	const std::string ParticleShaderSource::vertexShader = 
R"(#version 400

in vec2 position;

in mat4 viewMatrix;
in vec4 texOffset;
in float blendFactor;

out vec2 textureCoords1;
out vec2 textureCoords2;
out float blend;

uniform mat4 projectionMatrix;
uniform float numberOfRows;

void main(void) {

	vec2 textureCoords = position + vec2(0.5);
	textureCoords.y = 1.0 - textureCoords.y;
	textureCoords /= numberOfRows;
	textureCoords1 = textureCoords + texOffset.xy;
	textureCoords2 = textureCoords + texOffset.zw;
	blend = blendFactor;

	gl_Position = projectionMatrix * viewMatrix * vec4(position, 0.0, 1.0);
	//gl_Position = vec4(position, 0.0, 1.0);

})";

	const std::string ParticleShaderSource::fragmentShader = 
R"(#version 400

layout (location = 0) out vec4 out_Color;
layout (location = 1) out vec4 out_LightColor;

in vec2 textureCoords1;
in vec2 textureCoords2;
in float blend;

uniform sampler2D particleTexture;

void main(void) {

	vec4 color1 = texture(particleTexture, textureCoords1);
	vec4 color2 = texture(particleTexture, textureCoords2);

	out_Color = mix(color1, color2, blend);
	out_LightColor = vec4(0.0);

})";

}