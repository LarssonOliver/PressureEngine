#include <chrono>
#include <vector>
#include "Engine.h"
#include "Callbacks.h"
#include "Graphics\OBJLoader.h"

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

		window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, true, false);

		GLenum err = glewInit();
		if (GLEW_OK != err) {
			std::cout << "GLEW Failed to initialize!" << std::endl;
			// TODO: Handle this error.
		}

		loader = new Loader();
		renderer = new MasterRenderer(window->getWindow());

		RawModel* model = OBJLoader::loadObjModel("dragon", *loader);
		ModelTexture* texture = new ModelTexture(loader->loadTexture("default.png"));
		TexturedModel* texturedModel = new TexturedModel(model, texture);
		entity = new Entity(*texturedModel, Vector3f(0, -5, -20), Vector3f(0, 0, 0), 1.f);
		entity->setRotationSpeed(0, 0.5f, 0);
		camera = new Camera();
		light = new Light(Vector3f(3, 10, 0), Vector3f(1));

	}

	void Engine::loop() {

#define PRESSURE_AMMOUNT_OF_TICKS 60.0;

		long lastTime = Math::getTimeNano();
		double ns = 1000000000 / PRESSURE_AMMOUNT_OF_TICKS;
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

#if 1
			if (Math::getTimeMillis() - timer > 1000) {
				timer += 1000;
				std::cout << "FPS: " << frames << std::endl;
				frames = 0;
			}
#endif
		}
	}

	void Engine::tick() {
		glfwPollEvents();
		if (window->resized) {
			renderer->updateProjectionMatrix();
			window->resized = false;
		}

		entity->tick();
	}

	void Engine::render() {
		renderer->processEntity(*entity);

		renderer->render(*light, *camera);
		glfwSwapBuffers(window->getWindow());
	}

	void Engine::terminate() {
		loader->cleanUp();
		renderer->cleanUp();

		delete window;
		delete loader;
		delete renderer;
		delete entity;
		delete camera;
		delete light;

		glfwTerminate();
	}

}
