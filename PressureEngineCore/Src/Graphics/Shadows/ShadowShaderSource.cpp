#include "ShadowShaderSource.h"

namespace Pressure {
	
	const std::string ShadowShaderSource::vertexShader = 
R"(#version 150

in vec3 in_position;

uniform mat4 mvpMatrix;

void main(void) {
	
	gl_Position = mvpMatrix * vec4(in_position, 1.0); 

})";

	const std::string ShadowShaderSource::fragmentShader = 
R"(#version 330

out vec4 out_color;

uniform sampler2D modelTexture;

void main(void) {

	out_color = vec4(1.0);

})";

}