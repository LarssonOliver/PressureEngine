#version 400

in vec2 position;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main(void) {

	gl_Position = projectionMatrix * viewMatrix * vec4(position, 0.0, 1.0);
	//gl_Position = vec4(position, 0.0, 1.0);

}