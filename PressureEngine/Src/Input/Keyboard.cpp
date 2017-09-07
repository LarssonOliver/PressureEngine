#include "Keyboard.h"
#include <algorithm>

namespace Pressure {

	Keyboard* Keyboard::inst(0);

	Keyboard* Keyboard::Inst() {
		if (!inst) 
			inst = new Keyboard();		
		return inst;
	}

	bool Keyboard::isPressed(int key) {
		return Inst()->keys[key];
	}

	void Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Inst()->keys[key] = action != GLFW_RELEASE;
	}

	Keyboard::Keyboard() 
		: keys(GLFW_KEY_LAST) {
		std::fill(keys.begin(), keys.end(), false);
	}

}