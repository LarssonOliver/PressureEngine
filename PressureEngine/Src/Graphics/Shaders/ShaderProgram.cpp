#include "ShaderProgram.h"
#include "EntityShader.h"

namespace Pressure {

	void ShaderProgram::loadShaders(const std::string& vertexShader, const std::string& fragmentShader) {
		vertexShaderID = loadShader(vertexShader, GL_VERTEX_SHADER);
		geometryShaderID = 0;
		fragmentShaderID = loadShader(fragmentShader, GL_FRAGMENT_SHADER);
		programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
		bindAttributes();
		glLinkProgram(programID);
		glValidateProgram(programID);
		getAllUniformLocations();
	}

	void ShaderProgram::loadShaders(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader) {
		vertexShaderID = loadShader(vertexShader, GL_VERTEX_SHADER);
		geometryShaderID = loadShader(geometryShader, GL_GEOMETRY_SHADER);
		fragmentShaderID = loadShader(fragmentShader, GL_FRAGMENT_SHADER);
		programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, geometryShaderID);
		glAttachShader(programID, fragmentShaderID);
		bindAttributes();
		glLinkProgram(programID);
		glValidateProgram(programID);
		getAllUniformLocations();
	}

	void ShaderProgram::start() {
		glUseProgram(programID);
	}

	void ShaderProgram::stop() {
		glUseProgram(0);
	}

	void ShaderProgram::cleanUp() {
		stop();
		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteProgram(programID);
	}

	void ShaderProgram::bindAttribute(int attribute, const char* variableName) {
		glBindAttribLocation(programID, attribute, variableName);
	}

	int ShaderProgram::getUniformLocation(const char* uniformName) {
		return glGetUniformLocation(programID, uniformName);
	}

	void ShaderProgram::loadFloat(const int location, const float value) {
		glUniform1f(location, value);
	}

	void ShaderProgram::loadVector(const int location, const Vector2f& value) {
		glUniform2f(location, value.getX(), value.getY());
	}

	void ShaderProgram::loadVector(const int location, const Vector3f& value) {
		glUniform3f(location, value.getX(), value.getY(), value.getZ());
	}

	void ShaderProgram::loadVector(const int location, const Vector4f& value) {
		glUniform4f(location, value.getX(), value.getY(), value.getZ(), value.getW());
	}

	void ShaderProgram::loadBool(const int location, const bool value) {
		glUniform1f(location, value);
	}

	void ShaderProgram::loadMatrix(const int location, Matrix4f& value) {
		glUniformMatrix4fv(location, 1, GL_FALSE, value.getArray());
	}

	void ShaderProgram::loadInt(const int location, const int value) {
		glUniform1i(location, value);
	}

	unsigned int ShaderProgram::loadShader(const std::string& shader, GLenum type) {
		unsigned int shaderID = glCreateShader(type);

		const char* shaderSrc = shader.c_str();

		int result = GL_FALSE;
		int logLength;

		// Compile Shader
		glShaderSource(shaderID, 1, &shaderSrc, NULL);
		glCompileShader(shaderID);

		//Check Shader
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		if (!result) {
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<GLchar> shaderError((logLength > 1) ? logLength : 1);
			glGetShaderInfoLog(shaderID, logLength, NULL, &shaderError[0]);
			std::cout << &shaderError[0] << std::endl;
		}

		return shaderID;
	}

}

