#pragma once
#include "../../Common.h"

namespace Pressure {

	class Shader {

	private:
		int m_ProgramID;
		int m_VertexShaderID;
		int m_GeometryShaderID;
		int m_FragmentShaderID;

	public:
		void loadShaders(const std::string& vertexShader, const std::string& fragmentShader);
		void loadShaders(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader);		

	private:
		unsigned int loadShader(const std::string& shader, GLenum type);

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
		void loadVector(const int location, const Vector2f& value);
		void loadVector(const int location, const Vector3f& value);
		void loadVector(const int location, const Vector4f& value);
		void loadBool(const int location, const bool value);
		void loadMatrix(const int location, Matrix4f& value);
		void loadInt(const int location, const int value);

	};

}