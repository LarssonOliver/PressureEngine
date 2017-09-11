#include "EntityShader.h"

namespace Pressure {

	EntityShader::EntityShader() {
		ShaderProgram::loadShaders(PRESSURE_ENGINE_STATIC_VERTEX_FILE, PRESSURE_ENGINE_STATIC_FRAGMENT_FILE);
	}

	void EntityShader::bindAttributes() {
		ShaderProgram::bindAttribute(0, "position");
		ShaderProgram::bindAttribute(1, "textureCoords");
		ShaderProgram::bindAttribute(2, "normal");
	}

	void EntityShader::getAllUniformLocations() {
		location_transformationMatrix = ShaderProgram::getUniformLocation("transformationMatrix");
		location_projectionMatrix = ShaderProgram::getUniformLocation("projectionMatrix");
		location_viewMatrix = ShaderProgram::getUniformLocation("viewMatrix");
		location_lightPosition = ShaderProgram::getUniformLocation("lightPosition");
		location_lightColor = ShaderProgram::getUniformLocation("lightColor");
		location_shineDamper = ShaderProgram::getUniformLocation("shineDamper");
		location_reflectivity = ShaderProgram::getUniformLocation("reflectivity");
		location_fakeLighting = ShaderProgram::getUniformLocation("fakeLighting");
	}

	void EntityShader::loadTransformationMatrix(Matrix4f& matrix) {
		ShaderProgram::loadMatrix(location_transformationMatrix, matrix);
	}

	void EntityShader::loadProjectionmatrix(Matrix4f& matrix) {
		ShaderProgram::loadMatrix(location_projectionMatrix, matrix);
	}

	void EntityShader::loadViewMatrix(Camera& camera) {
		ShaderProgram::loadMatrix(location_viewMatrix, Matrix4f().createViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw(), camera.getRoll()));
	}

	void EntityShader::loadLight(Light& light) {
		ShaderProgram::loadVector(location_lightPosition, light.getPosition());
		ShaderProgram::loadVector(location_lightColor, light.getColor());
	}

	void EntityShader::loadShineVariables(float damper, float reflectivity) {
		ShaderProgram::loadFloat(location_shineDamper, damper);
		ShaderProgram::loadFloat(location_reflectivity, reflectivity);
	}

	void EntityShader::loadFakeLighting(bool useFakeLighting) {
		ShaderProgram::loadBool(location_fakeLighting, useFakeLighting);
	}

}