#pragma once
#include <GLFW\glfw3.h>

namespace Pressure {

	class Window {
	private:
		GLFWwindow* window;

		int width;
		int height;

		const char* title;
		bool fullscreen;
		bool vsync;		
	
	public: 
		Window(int width, int height, const char* title, bool fullscreen, bool vsync);
		~Window();
		
		void tick();
		void setTitle(const char* title);

		int getWidth() const;
		int getHeight() const;
		GLFWwindow* getWindow() const;

		void setVsync(bool enabled);
		bool isVsync() const;

	private: 
		bool Init();

	};

}