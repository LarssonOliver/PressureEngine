#include "ShaderProgram.h"
#include "StaticShader.h"

namespace Pressure {

	void ShaderProgram::loadShaders(const char* vertexPath, const char* fragmentPath) {
		vertexShaderID = loadShader(vertexPath, GL_VERTEX_SHADER);
		fragmentShaderID = loadShader(fragmentPath, GL_FRAGMENT_SHADER);
		programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
		bindAttributes();
		glLinkProgram(programID);
		glValidateProgram(programID);
		getAllUniformLocations();
	}

	std::string ShaderProgram::readFile(const char* filePath) {
		std::string content;
		std::ifstream fileStream(filePath, std::ios::in);

		if (!fileStream.is_open()) {
			std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
			return "";
		}

		std::string line = "";
		while (!fileStream.eof()) {
			std::getline(fileStream, line);
			content.append(line + "\n");
		}

		fileStream.close();
		return content;

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

	unsigned int ShaderProgram::loadShader(const char* filePath, GLenum type) {
		unsigned int shaderID = glCreateShader(type);

		std::string shaderStr = readFile(filePath);
		const char* shaderSrc = shaderStr.c_str();

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

