#pragma once

#include "DllExport.h"
#include "Constants.h"
#include "Common.h"
#include "Callbacks.h"
#include "Math\Math.h"
#include "Input\Input.h"
#include "Graphics\GraphicsCommon.h"
#include "Services\Properties.h"
#include <Windows.h>
#include "Graphics\PostProcessing\PostProcessing.h"

namespace Pressure {

	class PRESSURE_API PressureEngine {

	private:
		bool m_Initialized = false;
		std::unique_ptr<Window> m_Window = nullptr;
		std::unique_ptr<Loader> m_Loader = nullptr;
		std::unique_ptr<Camera> m_Camera = nullptr;
		std::unique_ptr<MasterRenderer> m_Renderer = nullptr;
		std::unique_ptr<GuiRenderer> m_GuiRenderer = nullptr;
		std::unique_ptr<FrameBuffer> m_FrameBuffer = nullptr;
		std::unique_ptr<FrameBuffer> m_OutputBuffer = nullptr;
		std::unique_ptr<FrameBuffer> m_LightScatterBuffer = nullptr;

		std::vector<Light> m_Lights;
		std::vector<GuiTexture> m_Guis;

	public:
		// Always call this before anything else.
		void init(); 

		// Called at start of every tick;
		void tick();

		// Adds to renderbatch.
		void process(Entity& entity);
		void process(std::vector<Entity>& entities);

		void process(Water& water);
		void process(std::vector<Water>& waters);

		// First light will always be counted as sun.
		void process(Light& light);
		void process(std::vector<Light>& lights);

		void process(GuiTexture& gui);
		void process(std::vector<GuiTexture>& guis);

		// Renders the scene after all elements are processed.
		void render();

		// Loads model.
		RawModel loadObjModel(const char* fileName); // Filename excluding .obj extension.
		ModelTexture loadTexture(const char* filePath); // Filename including extension.
		TexturedModel loadModel(const char* objName, const char* texturePath);
		ParticleTexture loadParticleTexture(const char* filePath, const unsigned int numberOfRows, const bool additiveBlending = false);

		Water generateWater(const Vector3f& position) const;

		Window& getWindow() { return *m_Window; };

		const bool isInitialized() const { return m_Initialized; }

		// Call after operation.
		void terminate();

	private:
		void enableErrorCallbacks();

	};

}