#include "Shader.h"

namespace Pressure {

	void Shader::loadShaders(const std::string& vertexShader, const std::string& fragmentShader) {
		m_VertexShaderID = loadShader(vertexShader, GL_VERTEX_SHADER);
		m_GeometryShaderID = 0;
		m_FragmentShaderID = loadShader(fragmentShader, GL_FRAGMENT_SHADER);
		m_ProgramID = glCreateProgram();
		glAttachShader(m_ProgramID, m_VertexShaderID);
		glAttachShader(m_ProgramID, m_FragmentShaderID);
		bindAttributes();
		glLinkProgram(m_ProgramID);
		glValidateProgram(m_ProgramID);
		getAllUniformLocations();
	}

	void Shader::loadShaders(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader) {
		if (strcmp((const char*)glGetString(GL_VENDOR), "Intel") == 0) { // Can't run geometry shader on intel.	
			return loadShaders(vertexShader, fragmentShader);
		}
		m_VertexShaderID = loadShader(vertexShader, GL_VERTEX_SHADER);
		m_GeometryShaderID = loadShader(geometryShader, GL_GEOMETRY_SHADER);
		m_FragmentShaderID = loadShader(fragmentShader, GL_FRAGMENT_SHADER);
		m_ProgramID = glCreateProgram();
		glAttachShader(m_ProgramID, m_VertexShaderID);
		glAttachShader(m_ProgramID, m_GeometryShaderID);
		glAttachShader(m_ProgramID, m_FragmentShaderID);
		bindAttributes();
		glLinkProgram(m_ProgramID);
		glValidateProgram(m_ProgramID);
		getAllUniformLocations();
	}

	void Shader::start() {
		glUseProgram(m_ProgramID);
	}

	void Shader::stop() {
		glUseProgram(0);
	}

	void Shader::cleanUp() {
		stop();
		glDetachShader(m_ProgramID, m_VertexShaderID);
		glDetachShader(m_ProgramID, m_FragmentShaderID);
		glDeleteShader(m_VertexShaderID);
		glDeleteShader(m_FragmentShaderID);
		glDeleteProgram(m_ProgramID);
	}

	void Shader::bindAttribute(int attribute, const char* variableName) {
		glBindAttribLocation(m_ProgramID, attribute, variableName);
	}

	int Shader::getUniformLocation(const char* uniformName) {
		return glGetUniformLocation(m_ProgramID, uniformName);
	}

	void Shader::loadFloat(const int location, const float value) {
		glUniform1f(location, value);
	}

	void Shader::loadVector(const int location, const Vector2f& value) {
		glUniform2f(location, value.getX(), value.getY());
	}

	void Shader::loadVector(const int location, const Vector3f& value) {
		glUniform3f(location, value.getX(), value.getY(), value.getZ());
	}

	void Shader::loadVector(const int location, const Vector4f& value) {
		glUniform4f(location, value.getX(), value.getY(), value.getZ(), value.getW());
	}

	void Shader::loadBool(const int location, const bool value) {
		glUniform1f(location, value);
	}

	void Shader::loadMatrix(const int location, Matrix4f& value) {
		glUniformMatrix4fv(location, 1, GL_FALSE, value.getArray());
	}

	void Shader::loadInt(const int location, const int value) {
		glUniform1i(location, value);
	}

	unsigned int Shader::loadShader(const std::string& shader, GLenum type) {
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
			PRESSURE_LOG(LOG_ERROR) << &shaderError[0] << std::endl;
		}

		return shaderID;
	}

}

