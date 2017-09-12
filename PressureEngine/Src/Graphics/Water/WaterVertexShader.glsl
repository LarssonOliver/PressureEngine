#version 400

in vec3 position;

out vec3 normal;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform float waveModifier;

void main(void) {
	
	//normal = (transformationMatrix * vec4(0.0, 1.0, 0.0, 0.0)).xyz;
	normal = vec3(0.0, 1.0, 0.0);

	vec3 wavePos = vec3(position.x, sin((degrees(position.x) + waveModifier)), position.z);

	gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(wavePos, 1.0);

}