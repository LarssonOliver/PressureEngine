#include "Mouse.h"
#include <algorithm>

namespace Pressure {

	Mouse* Mouse::inst(0);

	Mouse* Mouse::Inst() {
		if (!inst)
			inst = new Mouse();
		return inst;
	}

	bool Mouse::isPressed(GLint key) {
		return Inst()->buttons[key];
	}

	float Mouse::getDWheel() {
		float s = Inst()->scroll;
		Inst()->scroll = 0;
		return s;
	}

	float Mouse::getDX() {
		float dx = Inst()->dx;
		Inst()->dx = 0;
		return dx;
	}

	float Mouse::getDY() {
		float dy = Inst()->dy;
		Inst()->dy = 0;
		return dy;
	}

	void Mouse::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		Inst()->buttons[button] = action != GLFW_RELEASE;
	}

	void Mouse::mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		Inst()->scroll += yoffset;
	}

	void Mouse::mouse_pos_callback(GLFWwindow* window, double xpos, double ypos) {
		Inst()->dx = 0 + xpos - Inst()->last_xpos;
		Inst()->last_xpos = xpos;
		Inst()->dy = 0 + ypos - Inst()->last_ypos;
		Inst()->last_ypos = ypos;
	}

	Mouse::Mouse()
		: buttons(GLFW_MOUSE_BUTTON_LAST), scroll(0), last_xpos(0), last_ypos(0) {
		std::fill(buttons.begin(), buttons.end(), false);
	}

}
