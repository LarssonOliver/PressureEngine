#include "PressureEngine.h"

namespace Pressure {

	void PressureEngine::init() {
		// Initialize GLFW.
		if (!glfwInit()) {
			std::cout << "GLFW Failed to initialize!" << std::endl;
			__debugbreak();
		}

		window = std::make_unique<Window>(std::stoi(Properties::Inst()->get("windowWidth")),
			std::stoi(Properties::Inst()->get("windowHeight")), Properties::Inst()->get("windowTitle").c_str(),
			std::stoi(Properties::Inst()->get("windowFullscreen")), std::stoi(Properties::Inst()->get("windowVsync")));
		
		// Initialize GLEW.
		unsigned int err = glewInit();
		if (GLEW_OK != err) {
			std::cout << "GLEW Failed to initialize!" << std::endl;
			__debugbreak();
		}

		//std::cout << glGetString(GL_VENDOR) << std::endl;

#ifdef PRESSURE_DEBUG
		// Enable OpenGL debugging callback.
		enableErrorCallbacks();
#endif
		// Hide console if specified in properties file.
		if (std::stoi(Properties::Inst()->get("hideConsole")))
			::ShowWindow(::GetConsoleWindow(), SW_HIDE);

		loader = std::make_unique<Loader>();
		camera = std::make_unique<Camera>();
		renderer = std::make_unique<MasterRenderer>(*window, *loader, *camera);
		guiRenderer = std::make_unique<GuiRenderer>(*loader);
		ParticleMaster::init(*loader, window->getWindow());		
		
		frameBuffer = std::make_unique<FrameBuffer>(*window, window->getWidth(), window->getHeight(), true);
		outputBuffer = std::make_unique<FrameBuffer>(*window, window->getWidth(), window->getHeight(), DepthBufferType::RENDER_BUFFER);
		PostProcessing::init(*loader);

		initialized = true;
	}

	void PressureEngine::tick() {
		glfwPollEvents();
		camera->tick();

		if (window->resized) {
			renderer->updateProjectionMatrix();
			window->resized = false;
		}

		renderer->tick();
		ParticleMaster::tick(*camera);
	}

	void PressureEngine::process(Entity& entity) {
		renderer->processEntity(entity);
	}

	void PressureEngine::process(std::vector<Entity>& entities) {
		for (auto& entity : entities) {
			process(entity);
		}
	}

	void PressureEngine::process(Water& water) {
		renderer->processWater(water);
	}

	void PressureEngine::process(std::vector<Water>& water) {
		for (auto& w : water) {
			process(w);
		}
	}

	void PressureEngine::process(Light& light) {
		lights.push_back(light);
	}

	void PressureEngine::process(std::vector<Light>& light) {
		lights.insert(std::end(lights), std::begin(light), std::end(light));
	}

	void PressureEngine::process(GuiTexture& gui) {
		guis.push_back(gui);
	}

	void PressureEngine::process(std::vector<GuiTexture>& gui) {
		guis.insert(std::end(guis), std::begin(gui), std::end(gui));
	}

	void PressureEngine::render() {
		if (lights.size() > 0)
			renderer->renderShadowMap(lights[0]);
		renderer->renderWaterFrameBuffers(lights, *camera);

		frameBuffer->bind();
		renderer->render(lights, *camera);
		ParticleMaster::renderParticles(*camera);
		frameBuffer->unbind();
		frameBuffer->resolveToFrameBuffer(GL_COLOR_ATTACHMENT0, *outputBuffer);
		PostProcessing::process(outputBuffer->getColorTexture());

		guiRenderer->render(guis);
		
		window->swapBuffers();
		lights.clear();
		guis.clear();
	}

	RawModel PressureEngine::loadObjModel(const char* fileName) {
		return OBJLoader::load(fileName, *loader);	
	}

	ModelTexture PressureEngine::loadTexture(const char* filePath) {
		return ModelTexture(loader->loadTexture(filePath));		
	}

	ParticleTexture PressureEngine::loadParticleTexture(const char* filePath, const unsigned int numberOfRows, const bool additiveBlending) {
		return ParticleTexture(loader->loadTexture(filePath), numberOfRows, additiveBlending);
	}

	Water PressureEngine::generateWater(const Vector3f& position) const {
		return Water(position, *loader);		
	}

	void PressureEngine::enableErrorCallbacks() {
		// Enable GLFW debugging callback.
		glfwSetErrorCallback(Callbacks::glfw_error_callback);

		// Enable GLEW debugging callback.
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		if (glDebugMessageCallback) {
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(opengl_error_callback, nullptr);
			unsigned int unusedIds = 0;
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
		}
		else
			std::cout << "glDebugMessageCallback Not Available! Disabling OpenGL Error Handling." << std::endl;
	}

	void PressureEngine::terminate() {
		renderer->cleanUp();
		ParticleMaster::cleanUp();
		glfwTerminate();
	}

}