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
out vec4 out_Color;

uniform samplerCube cubeMap;

void main(void){
    out_Color = texture(cubeMap, textureCoords);
})";

}