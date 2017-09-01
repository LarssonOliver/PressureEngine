#include "Callbacks.h"
#include "Math\Math.h"
#include <iostream>

namespace Pressure {

	void Callbacks::error_callback(int error, const char* description) {
		fprintf(stderr, "Error: %s\n", description);
	}

	void Callbacks::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);

		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
			std::cout << Math::getTimeMillis() << std::endl;
	}

}