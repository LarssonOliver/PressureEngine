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
		location_shineDamper = ShaderProgram::getUniformLocation("shineDamper");
		location_reflectivity = ShaderProgram::getUniformLocation("reflectivity");
		location_fakeLighting = ShaderProgram::getUniformLocation("fakeLighting");
		location_plane = ShaderProgram::getUniformLocation("plane");

		for (int i = 0; i < 4; i++) {
			location_lightColor[i] = ShaderProgram::getUniformLocation(("lightColor[" + std::to_string(i) + "]").c_str());
			location_lightPosition[i] = ShaderProgram::getUniformLocation(("lightPosition[" + std::to_string(i) + "]").c_str());
			location_attenuation[i] = ShaderProgram::getUniformLocation(("attenuation[" + std::to_string(i) + "]").c_str());
		}
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

	void EntityShader::loadLights(std::vector<Light>& lights) {
		for (unsigned int i = 0; i < 4; i++) {
			if (i < lights.size()) {
				ShaderProgram::loadVector(location_lightPosition[i], lights[i].getPosition());
				ShaderProgram::loadVector(location_lightColor[i], lights[i].getColor());	
				ShaderProgram::loadVector(location_attenuation[i], lights[i].getAttenuation());
			} else {
				ShaderProgram::loadVector(location_lightPosition[i], Vector3f(0));
				ShaderProgram::loadVector(location_lightColor[i], Vector3f(0));
				ShaderProgram::loadVector(location_attenuation[i], Vector3f(1, 0, 0));
			}
		}
	}

	void EntityShader::loadShineVariables(float damper, float reflectivity) {
		ShaderProgram::loadFloat(location_shineDamper, damper);
		ShaderProgram::loadFloat(location_reflectivity, reflectivity);
	}

	void EntityShader::loadFakeLighting(bool useFakeLighting) {
		ShaderProgram::loadBool(location_fakeLighting, useFakeLighting);
	}

	void EntityShader::loadClipPlane(const Vector4f& plane) {
		ShaderProgram::loadVector(location_plane, plane);
	}

}