#include "Shaders.h"

namespace Pressure {
		
	const std::string Shaders::vertexShader = 
R"(#version 330 core

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out VertexData {
	vec2 pass_textureCoords;
	vec3 surfaceNormal;
	vec3 toLightVector[4];
	vec3 toCameraVector;
	vec4 shadowCoords;
} vertexOut;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition[4];
uniform float useFakeLighting;
uniform vec4 plane;
uniform float windModifier;

uniform mat4 toShadowMapSpace;

const float shadowDistance = 150.0;
const float transitionDistance = 10.0;

float getWindX() {
	return 0.2 * (0.4 * sin(4 * windModifier) + 0.2 * sin(7.2 * windModifier) + 0.4 * sin(-windModifier));
}

float getWindZ() {
	return 0.2 * (0.4 * sin(4 * windModifier) + 0.4 * sin(6 * windModifier) + 0.2 * sin(-windModifier));
}

void main(void) {

	vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
	worldPosition.xz = vec2(worldPosition.x + position.y * getWindX(), worldPosition.z + position.y * getWindZ());
	vertexOut.shadowCoords = toShadowMapSpace * worldPosition;

	gl_ClipDistance[0] = dot(worldPosition, plane);

	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	vertexOut.pass_textureCoords = textureCoords;

	vec3 actualNormal = normal;
	if (useFakeLighting > 0.5) {
		actualNormal = vec3(0.0, 1.0, 0.0);
	}

	vertexOut.surfaceNormal = (transformationMatrix * vec4(actualNormal, 0.0)).xyz;
	for(int i = 0; i < 4; i++) {
		vertexOut.toLightVector[i] = lightPosition[i] - worldPosition.xyz;	
	}
	vertexOut.toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;

	float distance = length((viewMatrix * worldPosition).xyz);
	distance = distance - (shadowDistance - transitionDistance);
	distance = distance / transitionDistance;
	vertexOut.shadowCoords.w = clamp(1.0 - distance, 0.0, 1.0);

})";

	const std::string Shaders::geometryShader = 
R"(#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VertexData {
	vec2 pass_textureCoords;
	vec3 surfaceNormal;
	vec3 toLightVector[4];
	vec3 toCameraVector;
	vec4 shadowCoords;
} vertexIn[3];

out VertexData {
	vec2 pass_textureCoords;
	vec3 surfaceNormal;
	vec3 toLightVector[4];
	vec3 toCameraVector;
	vec4 shadowCoords;
} vertexOut;

void main(void) {
	for (int i = 0; i < 3; i++) {
		vertexOut.pass_textureCoords = (vertexIn[0].pass_textureCoords + vertexIn[1].pass_textureCoords + vertexIn[2].pass_textureCoords) / 3;
		vertexOut.toCameraVector = vertexIn[i].toCameraVector;
		vertexOut.shadowCoords = vertexIn[i].shadowCoords;

		vertexOut.surfaceNormal = (vertexIn[0].surfaceNormal + vertexIn[1].surfaceNormal + vertexIn[2].surfaceNormal) / 3;
		vertexOut.toLightVector = vertexIn[i].toLightVector;

		gl_Position = gl_in[i].gl_Position;
		gl_ClipDistance[0] = gl_in[i].gl_ClipDistance[0];
		EmitVertex();
	}
	EndPrimitive();
})";

	const std::string Shaders::fragmentShader = 
R"(#version 330 core

in VertexData {
	vec2 pass_textureCoords;
	vec3 surfaceNormal;
	vec3 toLightVector[4];
	vec3 toCameraVector;
	vec4 shadowCoords;
} vertexIn;

out vec4 out_Color;

uniform sampler2D textureSampler;
uniform sampler2D shadowMap;

uniform vec3 lightColor[4];
uniform vec3 attenuation[4];
uniform float shineDamper;
uniform float reflectivity;

const int pcfCount = 2;
const float totalTexels = (pcfCount * 2.0 + 1.0) * (pcfCount * 2.0 + 1.0);

void main(void) {

	const float shadowMapSize = 8192;
	float texelSize = 1.0 / shadowMapSize;
	float total = 0.0;	

	for(int x = -pcfCount; x <= pcfCount; x++) {	
		for(int y = -pcfCount; y <= pcfCount; y++) {
			float objectNearestLight = texture(shadowMap, vertexIn.shadowCoords.xy + vec2(x, y) * texelSize).r;
			if(vertexIn.shadowCoords.z > objectNearestLight) {
				total += 1.0;
			}
		}	
	}

	total /= totalTexels;
	float lightFactor = 1.0 - (total * vertexIn.shadowCoords.w);


	vec3 unitNormal = normalize(vertexIn.surfaceNormal);
	vec3 unitVectorToCamera = normalize(vertexIn.toCameraVector);

	vec3 totalDiffuse = vec3(0.0);
	vec3 totalSpecular = vec3(0.0);

	for(int i = 0; i < 4; i++) {
		float distance = length(vertexIn.toLightVector[i]);
		float attFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);
		vec3 unitLightVector = normalize(vertexIn.toLightVector[i]);
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
	totalDiffuse = max(totalDiffuse * lightFactor, 0.2);

	vec4 textureColor = texture(textureSampler, vertexIn.pass_textureCoords);
	if (textureColor.a < 0.5) {
		discard;
	}

	out_Color = vec4(totalDiffuse, 1.0) * textureColor + vec4(totalSpecular * lightFactor, 1.0);
	//out_Color = vec4(totalDiffuse, 1.0) * textureColor;
	//out_Color = vec4(lightFactor);
	//out_Color = vertexIn.shadowCoords;

})";

}