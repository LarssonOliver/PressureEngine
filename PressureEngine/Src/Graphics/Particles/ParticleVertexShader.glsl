#version 400

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

}