#pragma once

#include <vector>
#include <GLFW\glfw3.h>
#include "../DllExport.h"

namespace Pressure {

	// Singleton class for keyboard input.
	class PRESSURE_API Keyboard {

	private:
		std::vector<bool> m_Keys;
		static Keyboard* s_Inst;

	public:
		static Keyboard* Inst();
		static bool isPressed(int key);

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	protected:
		Keyboard();
		Keyboard(const Keyboard& tm) = delete;
		
	};

}
