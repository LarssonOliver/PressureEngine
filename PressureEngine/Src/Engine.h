#pragma once
#include "Common.h"
#include "Graphics\Window.h"
#include "Graphics\Loader.h"
#include "Graphics\Shaders\Renderer.h"
#include "Graphics\Shaders\EntityShader.h"
#include "Graphics\GraphicsCommon.h"
#include "Graphics\Water\Water.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "PressureEngine"

namespace Pressure {

	class Engine {

	private:
		Window* window;
		Loader* loader;

		MasterRenderer* renderer;
		Entity* entity;
		Light* light;
		Camera* camera;

		Water* water;

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
