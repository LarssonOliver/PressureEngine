#include <chrono>
#include <vector>
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
		loader = new Loader();
		renderer = new Renderer();
		
		std::vector<float> vertices = { -0.5f, 0.5f, 0.f, -0.5f, -0.5f, 0.f, 0.5f, -0.5f, 0.f, 0.5f, -0.5f, 0.f, 0.5f, 0.5f, 0.f, -0.5f, 0.5f, 0.f };

		model = loader->loadToVao(vertices);

	}

	void Engine::loop() {

#define PRESSURE_ENGINE_AMMOUNT_OF_TICKS 60.0;

		long lastTime = Math::getTimeNano();
		double ns = 1000000000 / PRESSURE_ENGINE_AMMOUNT_OF_TICKS;
		double delta = 0;
		long timer = Math::getTimeMillis();
		int frames = 0;
		long now;

		while (!glfwWindowShouldClose(window->getWindow())) {
			now = Math::getTimeNano();
			delta += (now - lastTime) / ns;
			lastTime = now;

			while (delta >= 1) {
				tick();
				delta--;
			}

			if (!glfwWindowShouldClose(window->getWindow()))
				render();
			frames++;

			if (Math::getTimeMillis() - timer > 1000) {
				timer += 1000;
				std::cout << "FPS: " << frames << std::endl;
				frames = 0;
			}
		}
	}

	void Engine::terminate() {
		loader->cleanUp();
		delete loader;
		delete renderer;
		delete window;
		delete model;
		glfwTerminate();
	}

	void Engine::tick() {
		glfwPollEvents();		
	}

	void Engine::render() {
		renderer->prepare();
		renderer->render(*model);

		glfwSwapBuffers(window->getWindow());
	}

}
