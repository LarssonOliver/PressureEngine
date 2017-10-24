#pragma once

#include <vector>
#include <GLFW\glfw3.h>

namespace Pressure {

	// Singleton class for mouse input.
	class Mouse {

	public:
		static Mouse* Inst();
		static bool isPressed(GLint key);
		static float getDWheel();
		static float getDX();
		static float getDY();
		
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		static void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);

	protected:
		Mouse();
		Mouse(const Mouse& tm) = delete;

		static Mouse* inst;
		std::vector<bool> buttons;
		float scroll;

		float dx, dy;
		float last_xpos, last_ypos;

	};

}
