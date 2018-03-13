#include "Callbacks.h"
#include "Math\Math.h"
#include <iostream>

namespace Pressure {

	void Callbacks::glfw_error_callback(int error, const char* description) {
		fprintf(stderr, "Error: %s\n", description);
	}

	void APIENTRY Callbacks::opengl_error_callback(GLenum soruce, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		using namespace std;

		// Not interested in notifications.
		if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
			return;
		else if (severity == GL_DEBUG_SEVERITY_LOW)
			return;

		cout << "*** [OpengGL Error START] ***" << endl;
		cout << "[Message]: " << message << endl;
		cout << "[Type]: ";
		switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			cout << "ERROR";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			cout << "DEPRECATED_BEHAVIOR";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			cout << "UNDEFINED_BEHAVIOR";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			cout << "PORTABILITY";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			cout << "PERFORMANCE";
			break;
		case GL_DEBUG_TYPE_OTHER:
			cout << "OTHER";
			break;
		}
		cout << endl;

		cout << "[Id]: " << id << endl;
		cout << "[Severity]: ";
		switch (severity) {
		case GL_DEBUG_SEVERITY_LOW:
			cout << "LOW";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			cout << "MEDIUM";
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			cout << "HIGH";
			break;
		}
		cout << endl;
		cout << "**** [OpengGL Error END] ****" << endl;

		if (severity == GL_DEBUG_SEVERITY_HIGH)
			__debugbreak();
	}

}