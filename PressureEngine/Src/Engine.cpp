#include "Common.h"
#include "Engine.h"
#include "Callbacks.h"

namespace Pressure {

	Engine::Engine() {		
		init();	
		loop();
		terminate();
	}

	void Engine::init() {
		if (!glfwInit()) {
			std::cout << "GLFW Failed to initialize!" << std::endl;
			// TODO: Handle this error.
		}

		glfwSetErrorCallback(Callbacks::error_callback);
		
		window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false, false);
		glClearColor(0.5, 0.5, 0.5, 1);
		
		glfwSetKeyCallback(window->getWindow(), Callbacks::key_callback); 

	}

	void Engine::loop() {

		while (!glfwWindowShouldClose(window->getWindow())) {
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window->getWindow());
			glfwPollEvents();
		}

	}

	void Engine::terminate() {
		delete window;
		glfwTerminate();
	}

}
