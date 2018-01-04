#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Pressure {

	struct Callbacks {

		static void glfw_error_callback(int error, const char* description);

	};

	// This function is required to be a C function by OpenGL.
	void APIENTRY opengl_error_callback(GLenum soruce, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	
}
