#version 400
//#line 1 "WaterFragmentShader.glsl"

in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;

out vec4 out_Color;

uniform vec3 lightColor;

float shineDamper = 10;
float reflectivity = 0.8;

vec3 waterColor = vec3(0.0, 0.6, 1.0);

void main(void) {

	float nDot1 = dot(surfaceNormal, toLightVector);
	float brightness = max(nDot1, 0.1);
	vec3 diffuse = brightness * lightColor;

	vec3 lightDirection = -toLightVector;
	vec3 reflectedLightDirection = reflect(lightDirection, surfaceNormal);

	float specularFactor = dot(reflectedLightDirection, toCameraVector);
	specularFactor = max(specularFactor, 0.0);
	float dampedFactor = pow(specularFactor, shineDamper);
	vec3 finalSpecular = dampedFactor * reflectivity * lightColor;

	out_Color = vec4(diffuse, 1.0) * vec4(waterColor, 1.0) + vec4(finalSpecular, 1.0);
	//out_Color = vec4(diffuse, 1.0);
	//out_Color = vec4(finalSpecular, 1.0);

}