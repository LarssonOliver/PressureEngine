#pragma once
#include "../../Common.h"

namespace Pressure {

	class ShaderProgram {

	private:
		bool created = false;
		int programID;
		int vertexShaderID;
		int fragmentShaderID;

	public:
		void loadShaders(const char* vertexPath, const char* fragmentPath);
		bool isCreated() const { return created; }

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

	};

}