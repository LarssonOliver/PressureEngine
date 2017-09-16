#pragma once
#include "../../Common.h"

namespace Pressure {

	class ShaderProgram {

	private:
		int programID;
		int vertexShaderID;
		int fragmentShaderID;

	public:
		void loadShaders(const char* vertexPath, const char* fragmentPath);

	private:
		unsigned int loadShader(const char* filePath, GLenum type);
		std::string readFile(const char* filePath); // Req by loadShader()

	public:
		void start();
		void stop();
		void cleanUp();

	protected:
		virtual void bindAttributes() = 0;
		void bindAttribute(int attribute, const char* variableName);

		virtual void getAllUniformLocations() = 0;
		int getUniformLocation(const char* uniformName);

		void loadFloat(const int location, const float value);
		void loadVector(const int location, const Vector3f& value);
		void loadVector(const int location, const Vector4f& value);
		void loadBool(const int location, const bool value);
		void loadMatrix(const int location, Matrix4f& value);

	};

}