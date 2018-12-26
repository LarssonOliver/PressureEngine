#include "Keyboard.h"
#include <algorithm>

namespace Pressure {

	Keyboard* Keyboard::s_Inst(0);

	Keyboard* Keyboard::Inst() {
		if (!s_Inst) 
			s_Inst = new Keyboard();		
		return s_Inst;
	}

	bool Keyboard::isPressed(int key) {
		return Inst()->m_Keys[key];
	}

	void Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Inst()->m_Keys[key] = action != GLFW_RELEASE;
	}

	Keyboard::Keyboard() 
		: m_Keys(GLFW_KEY_LAST) {
		std::fill(m_Keys.begin(), m_Keys.end(), false);
	}

}