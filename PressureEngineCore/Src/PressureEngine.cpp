#include "PressureEngineCore/PressureEngine.h"

namespace Pressure {

	void PressureEngine::init() {
		// Initialize GLFW.
		if (!glfwInit()) {
			std::cout << "GLFW Failed to initialize!" << std::endl;
			__debugbreak();
		}

		m_Window = std::make_unique<Window>(std::stoi(Properties::get("windowWidth")),
			std::stoi(Properties::get("windowHeight")), Properties::get("windowTitle").c_str(),
			std::stoi(Properties::get("windowFullscreen")), std::stoi(Properties::get("windowVsync")));
		
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

#ifdef PRESSURE_DEBUG
		// Enable OpenGL debugging callback.
		enableErrorCallbacks();
#endif

		// Hide console if specified in properties file.
		if (std::stoi(Properties::get("hideConsole")))
			::ShowWindow(::GetConsoleWindow(), SW_HIDE);

		m_Loader = std::make_unique<Loader>();
		m_Camera = std::make_unique<Camera>();
		m_Renderer = std::make_unique<MasterRenderer>(*m_Window, *m_Loader, *m_Camera);
		m_GuiRenderer = std::make_unique<GuiRenderer>(*m_Loader);
		ParticleMaster::init(*m_Loader, m_Window->getWindow());		
		
		m_FrameBuffer = std::make_unique<FrameBuffer>(*m_Window, m_Window->getWidth(), m_Window->getHeight(), 2, 4, FrameBuffer::DepthBufferType::RENDER_BUFFER);
		m_OutputBuffer = std::make_unique<FrameBuffer>(*m_Window, m_Window->getWidth(), m_Window->getHeight(), 1, 1, FrameBuffer::DepthBufferType::TEXTURE);
		m_LightScatterBuffer = std::make_unique<FrameBuffer>(*m_Window, m_Window->getWidth(), m_Window->getHeight(), 1, 1, FrameBuffer::DepthBufferType::RENDER_BUFFER);
		PostProcessing::init(*m_Window, *m_Camera, *m_Loader);

		m_Initialized = true;
	}

	void PressureEngine::tick() {
		glfwPollEvents();
		m_Camera->tick();

		if (m_Window->resized) {
			m_Renderer->updateProjectionMatrix();
			PostProcessing::updateProjectionMatrix();
			ParticleMaster::updateProjectionMatrix(*m_Window);
			m_FrameBuffer = std::make_unique<FrameBuffer>(*m_Window, m_Window->getWidth(), m_Window->getHeight(), 2, 4, FrameBuffer::DepthBufferType::RENDER_BUFFER);
			m_OutputBuffer = std::make_unique<FrameBuffer>(*m_Window, m_Window->getWidth(), m_Window->getHeight(), 1, 1, FrameBuffer::DepthBufferType::TEXTURE);
			m_LightScatterBuffer = std::make_unique<FrameBuffer>(*m_Window, m_Window->getWidth(), m_Window->getHeight(), 1, 1, FrameBuffer::DepthBufferType::RENDER_BUFFER);
			m_Window->resized = false;
		}

		m_Renderer->tick();
		ParticleMaster::tick(*m_Camera);
	}

	void PressureEngine::process(Entity& entity) {
		m_Renderer->processEntity(entity);
	}

	void PressureEngine::process(std::vector<Entity>& entities) {
		for (auto& entity : entities) {
			process(entity);
		}
	}

	void PressureEngine::process(Water& water) {
		m_Renderer->processWater(water);
	}

	void PressureEngine::process(std::vector<Water>& water) {
		for (auto& w : water) {
			process(w);
		}
	}

	void PressureEngine::process(Light& light) {
		m_Lights.push_back(light);
	}

	void PressureEngine::process(std::vector<Light>& light) {
		m_Lights.insert(std::end(m_Lights), std::begin(light), std::end(light));
	}

	void PressureEngine::process(GuiTexture& gui) {
		m_Guis.push_back(gui);
	}

	void PressureEngine::process(std::vector<GuiTexture>& gui) {
		m_Guis.insert(std::end(m_Guis), std::begin(gui), std::end(gui));
	}

	void PressureEngine::render() {
		if (m_Lights.size() > 0)
			m_Renderer->renderShadowMap(m_Lights[0]);
		m_Renderer->renderWaterFrameBuffers(m_Lights, *m_Camera);

		m_FrameBuffer->bind();
		m_Renderer->render(m_Lights, *m_Camera);
		ParticleMaster::renderParticles(*m_Camera);
		m_FrameBuffer->unbind();
		m_FrameBuffer->resolve(0, *m_OutputBuffer);
		m_FrameBuffer->resolve(1, *m_LightScatterBuffer);
		PostProcessing::process(*m_OutputBuffer, m_LightScatterBuffer->getColorTexture(), m_Lights[0].getPosition());

		m_GuiRenderer->render(m_Guis);
		
		m_Window->swapBuffers();
		m_Lights.clear();
		m_Guis.clear();
	}

	RawModel PressureEngine::loadObjModel(const char* fileName) {
		return OBJLoader::load(fileName, *m_Loader);	
	}

	ModelTexture PressureEngine::loadTexture(const char* filePath) {
		return ModelTexture(m_Loader->loadTexture(filePath));		
	}

	TexturedModel PressureEngine::loadModel(const char* objName, const char* texturePath) {
		return TexturedModel(loadObjModel(objName), loadTexture(texturePath));
	}

	ParticleTexture PressureEngine::loadParticleTexture(const char* filePath, const unsigned int numberOfRows, const bool additiveBlending) {
		return ParticleTexture(m_Loader->loadTexture(filePath), numberOfRows, additiveBlending);
	}

	Water PressureEngine::generateWater(const Vector3f& position) const {
		return Water(position, *m_Loader);		
	}

	void PressureEngine::enableErrorCallbacks() {
		// Enable GLFW debugging callback.
		glfwSetErrorCallback(Callbacks::glfw_error_callback);

		// Enable GLEW debugging callback.
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		if (glDebugMessageCallback) {
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(Callbacks::opengl_error_callback, nullptr);
			unsigned int unusedIds = 0;
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
		}
		else
			std::cout << "glDebugMessageCallback Not Available! Disabling OpenGL Error Handling." << std::endl;
	}

	void PressureEngine::terminate() {
		m_Renderer->cleanUp();
		ParticleMaster::cleanUp();
		glfwTerminate();
	}

}