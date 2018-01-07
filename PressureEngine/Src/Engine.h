#pragma once
#include "DllExport.h"
#include "Common.h"
#include "Graphics\Window.h"
#include "Graphics\Loader.h"
#include "Graphics\Shaders\Renderer.h"
#include "Graphics\Shaders\EntityShader.h"
#include "Graphics\GraphicsCommon.h"
#include "Graphics\Water\Water.h"
#include "Graphics\Particles\ParticleSystem.h"
#include "Graphics\Guis\GuiRenderer.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "PressureEngine"

namespace Pressure {

	class PRESSURE_API Engine {

	private:
		Window* window;
		Loader* loader;

		MasterRenderer* renderer;
		Entity* entity;
		Entity* entity2;
		std::vector<Light>* lights;
		Camera* camera;

		ParticleSystem* particleSystem;

		Water* water;
		Water* water2;

		std::list<GuiTexture>* guis;
		GuiRenderer* guiRenderer;

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
