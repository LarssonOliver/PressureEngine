#include "Mouse.h"
#include <algorithm>

namespace Pressure {

	Mouse* Mouse::s_Inst(0);

	Mouse* Mouse::Inst() {
		if (!s_Inst)
			s_Inst = new Mouse();
		return s_Inst;
	}

	bool Mouse::isPressed(GLint key) {
		return Inst()->m_Buttons[key];
	}

	float Mouse::getDWheel() {
		float s = Inst()->m_Scroll;
		Inst()->m_Scroll = 0;
		return s;
	}

	float Mouse::getDX() {
		float dx = Inst()->m_dx;
		Inst()->m_dx = 0;
		return dx;
	}

	float Mouse::getDY() {
		float dy = Inst()->m_dy;
		Inst()->m_dy = 0;
		return dy;
	}

	void Mouse::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		Inst()->m_Buttons[button] = action != GLFW_RELEASE;
	}

	void Mouse::mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		Inst()->m_Scroll += (float) yoffset;
	}

	void Mouse::mouse_pos_callback(GLFWwindow* window, double xpos, double ypos) {
		Inst()->m_dx = 0 + (float) xpos - Inst()->m_LastXPos;
		Inst()->m_LastXPos = (float) xpos;
		Inst()->m_dy = 0 + (float) ypos - Inst()->m_LastYPos;
		Inst()->m_LastYPos = (float) ypos;
	}

	Mouse::Mouse()
		: m_Buttons(GLFW_MOUSE_BUTTON_LAST), m_Scroll(0), m_LastXPos(0), m_LastYPos(0) {
		std::fill(m_Buttons.begin(), m_Buttons.end(), false);
	}

}
