#version 400

in vec3 normal;

out vec4 out_Color;

void main(void) {

	float nDot1 = dot(vec3(0.0, 1.0, 0.0), normal);
	nDot1 = max(nDot1, 0.0);

	out_Color = vec4(0.0, 0.0, nDot1 * 1.0, 1.0);

}