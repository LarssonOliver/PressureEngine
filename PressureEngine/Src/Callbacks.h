#pragma once
#include <GLFW\glfw3.h>

namespace Pressure {

	struct Callbacks {

		static void error_callback(int error, const char* description);

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void window_resize_callback(GLFWwindow* window, int width, int height);

	};

}