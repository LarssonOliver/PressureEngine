#pragma once
#include "Graphics\Window.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "PressureEngine"

namespace Pressure {

	class Engine {

	private:
		Window* window;

	public:
		Engine();
	
	private: 
		void init();
		void loop();
		void terminate();

	private:
		void tick();
		void render();

	};

}
