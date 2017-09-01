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

		std::vector<float> vertices = {
			-0.5f, 0.5f, 0.f,
			-0.5f, -0.5f, 0.f,
			0.5f, -0.5f, 0.f,
			0.5f, 0.5f, 0.f
		};
		std::vector<int> indices = {  
			0, 1, 3,
			3, 1, 2
		};
		std::vector<float> textureCoords = {
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f
		};


		GLenum err = glewInit();
		if (GLEW_OK != err) {
			std::cout << "GLEW Failed to initialize!" << std::endl;
			// TODO: Handle this error.
		}

		loader = new Loader();
		shader = new StaticShader();
		renderer = new Renderer(*shader);

		RawModel* model = loader->loadToVao(vertices, textureCoords, indices);
		ModelTexture* texture = new ModelTexture(loader->loadTexture("2017-08-28.png"));
		TexturedModel* texturedModel = new TexturedModel(model, texture);
		entity = new Entity(*texturedModel, Vector3f(0, 0, 0), Vector3f(0, 0, 0), 1.f);

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

	void Engine::tick() {
		glfwPollEvents();		
		entity->tick();
		entity->move(0, 0, -.1);
	}

	void Engine::render() {
		renderer->prepare();
		shader->start();
		renderer->render(*entity, *shader);
		shader->stop();
		glfwSwapBuffers(window->getWindow());
	}

	void Engine::terminate() {
		loader->cleanUp();
		shader->cleanUp();

		delete window;
		delete loader;
		delete shader;
		delete renderer;
		delete entity;

		glfwTerminate();
	}

}
