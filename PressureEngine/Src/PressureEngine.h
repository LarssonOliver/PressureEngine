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
		bool initialized = false;
		std::unique_ptr<Window> window = nullptr;
		std::unique_ptr<Loader> loader = nullptr;
		std::unique_ptr<Camera> camera = nullptr;
		std::unique_ptr<MasterRenderer> renderer = nullptr;
		std::unique_ptr<GuiRenderer> guiRenderer = nullptr;
		std::unique_ptr<FrameBuffer> frameBuffer = nullptr;
		std::unique_ptr<FrameBuffer> outputBuffer = nullptr;
		std::unique_ptr<FrameBuffer> lightScatterBuffer = nullptr;

		std::vector<Light> lights;
		std::vector<GuiTexture> guis;

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
		RawModel loadObjModel(const char* fileNmae);
		ModelTexture loadTexture(const char* filePath);
		ParticleTexture loadParticleTexture(const char* filePath, const unsigned int numberOfRows, const bool additiveBlending = false);

		Water generateWater(const Vector3f& position) const;

		Window& getWindow() { return *window; };

		const bool isInitialized() const { return initialized; }

		// Call after operation.
		void terminate();

	private:
		void enableErrorCallbacks();

	};

}