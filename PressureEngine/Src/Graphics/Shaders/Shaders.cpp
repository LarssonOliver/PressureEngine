#include "Shaders.h"

namespace Pressure {
		
	const std::string Shaders::vertexShader = 
R"(#version 440

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 g_textureCoords;
out vec3 g_surfaceNormal;
out vec3 g_toLightVector[4];
out vec3 g_toCameraVector;
out vec4 g_shadowCoords;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition[4];
uniform float useFakeLighting;
uniform vec4 plane;

uniform mat4 toShadowMapSpace;

const float shadowDistance = 150.0;
const float transitionDistance = 10.0;

void main(void) {

	vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
	g_shadowCoords = toShadowMapSpace * worldPosition;
	g_shadowCoords.z -= 0.001; // Hack to stop shadows clipping the shadowmap.

	gl_ClipDistance[0] = dot(worldPosition, plane);

	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	g_textureCoords = textureCoords;

	vec3 actualNormal = normal;
	if (useFakeLighting > 0.5) {
		actualNormal = vec3(0.0, 1.0, 0.0);
	}

	g_surfaceNormal = (transformationMatrix * vec4(actualNormal, 0.0)).xyz;
	for(int i = 0; i < 4; i++) {
		g_toLightVector[i] = lightPosition[i] - worldPosition.xyz;	
	}
	g_toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;

	float distance = length((viewMatrix * worldPosition).xyz);
	distance = distance - (shadowDistance - transitionDistance);
	distance = distance / transitionDistance;
	g_shadowCoords.w = clamp(1.0 - distance, 0.0, 1.0);

})";

	const std::string Shaders::geometryShader = 
R"(#version 440

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec2 g_textureCoords[];
in vec3 g_surfaceNormal[];
in vec3 g_toLightVector[][4];
in vec3 g_toCameraVector[];
in vec4 g_shadowCoords[];

out vec2 textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector[4];
out vec3 toCameraVector;
out vec4 shadowCoords;

void main(void) {
	for (int i = 0; i < 3; i++) {
		textureCoords = g_textureCoords[i];
		toLightVector = g_toLightVector[i];
		toCameraVector = g_toCameraVector[i];
		shadowCoords = g_shadowCoords[i];
		surfaceNormal = (g_surfaceNormal[0] + g_surfaceNormal[1] + g_surfaceNormal[2]) / 3;
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
})";

	const std::string Shaders::fragmentShader = 
R"(#version 440

in vec2 textureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 toCameraVector;
in vec4 shadowCoords;

out vec4 out_Color;

uniform sampler2D textureSampler;
uniform sampler2D shadowMap;

uniform vec3 lightColor[4];
uniform vec3 attenuation[4];
uniform float shineDamper;
uniform float reflectivity;

const int pcfCount = 2;
const float totalTexels = (pcfCount * 2.2 + 1.0) * (pcfCount * 2.2 + 1.0);

void main(void) {

	const float shadowMapSize = 8192;
	float texelSize = 1.0 / shadowMapSize;
	float total = 0.0;

	for(int x = -pcfCount; x <= pcfCount; x++) {	
		for(int y = -pcfCount; y <= pcfCount; y++) {
			float objectNearestLight = texture(shadowMap, shadowCoords.xy + vec2(x, y) * texelSize).r;
			if(shadowCoords.z > objectNearestLight) {
				total += 1.0;
			}
		}	
	}

	total /= totalTexels;
	float lightFactor = 1.0 - (total * shadowCoords.w);


	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitVectorToCamera = normalize(toCameraVector);

	vec3 totalDiffuse = vec3(0.0);
	vec3 totalSpecular = vec3(0.0);

	for(int i = 0; i < 4; i++) {
		float distance = length(toLightVector[i]);
		float attFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);
		vec3 unitLightVector = normalize(toLightVector[i]);
		float nDot1 = dot(unitNormal, unitLightVector);
		float brightness = max(nDot1, 0.0);
		vec3 lightDirection = -unitLightVector;
		vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
		float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
		specularFactor = max(specularFactor, 0.0);
		float dampedFactor = pow(specularFactor, shineDamper);
		totalDiffuse += (brightness * lightColor[i]) / attFactor;
		totalSpecular += (dampedFactor * reflectivity * lightColor[i]) / attFactor;
	}
	totalDiffuse = max(totalDiffuse * lightFactor, 0.1);

	vec4 textureColor = texture(textureSampler, textureCoords);
	if (textureColor.a < 0.5) {
		discard;
	}

	out_Color = vec4(totalDiffuse, 1.0) * textureColor + vec4(totalSpecular * lightFactor, 1.0);
	//out_Color = vec4(lightFactor);

})";

}