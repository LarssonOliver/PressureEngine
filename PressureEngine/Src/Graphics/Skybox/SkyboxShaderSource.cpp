#include "SkyboxShaderSource.h"

namespace Pressure {
	
	const std::string SkyboxShaderSource::vertexShader = 
R"(#version 400

in vec3 position;
out vec3 textureCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main(void){
	
	gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0); 
	textureCoords = position;
	
})";

	const std::string SkyboxShaderSource::fragmentShader = 
R"(#version 400

in vec3 textureCoords;

layout (location = 0) out vec4 out_Color;
layout (location = 1) out vec4 out_LightColor;

uniform samplerCube cubeMap;

void main(void){

    out_Color = texture(cubeMap, textureCoords);
	out_LightColor = out_Color;
	if ((out_LightColor.r + out_LightColor.g + out_LightColor.b) > 2.5) {
		out_LightColor.rgb = vec3(0.8);
	} else {
		out_LightColor.rgb = vec3(0.1);
	}

})";

}