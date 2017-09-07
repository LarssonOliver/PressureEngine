#pragma once

#include <vector>
#include <GLFW\glfw3.h>

namespace Pressure {

	// Singleton class for keyboard input.
	class Keyboard {

	public:
		static Keyboard* Inst();
		static bool isPressed(int key);

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	protected:
		Keyboard();
		Keyboard(const Keyboard& tm) = delete;

		static Keyboard* inst;
		std::vector<bool> keys;
		
	};

}
