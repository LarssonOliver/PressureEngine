#version 400
//#line 1 "WaterFragmentShader.glsl"

in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;
in vec4 clipSpace;

out vec4 out_Color;

uniform vec3 lightColor;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D depthMap;

const float shineDamper = 10;
const float reflectivity = 0.8;

const vec4 waterColor = vec4(0.0, 0.6, 1.0, 1.0);
const float near = 0.1;
const float far = 1000.0;

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

	vec2 ndc = (clipSpace.xy/clipSpace.w) / 2.0 + 0.5;
	float depth = texture(depthMap, ndc).r;
	float floorDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
	depth = gl_FragCoord.z;
	float waterDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
	float waterDepth = floorDistance - waterDistance;

	vec2 distortion = ndc - vec2(surfaceNormal.x / 8.0, surfaceNormal.z / 8.0) * clamp(waterDepth / 20.0, 0.0, 1.0);
	distortion = clamp(distortion, 0.001, 0.999);
	vec4 reflectColor = texture(reflectionTexture, vec2(distortion.x, -distortion.y));
	vec4 refractColor = texture(refractionTexture, distortion);

	float refractiveFactor = dot(toCameraVector, surfaceNormal);
	finalSpecular *= clamp(waterDepth / 10.0, 0.0, 1.0);

	out_Color = vec4(diffuse, 1.0) * mix(reflectColor, refractColor, refractiveFactor) + vec4(finalSpecular, 1.0);
	out_Color = mix(out_Color, waterColor, 0.2);
	out_Color.a = clamp(waterDepth / 5.0, 0.0, 1.0);

}