#pragma once
#include <GLFW\glfw3.h>
#include "../DllExport.h"

namespace Pressure {

	class PRESSURE_API Window {

	private:
		GLFWwindow* m_Window;

		int m_Width;
		int m_Height;

		const char* m_Title;
		bool m_Fullscreen;
		bool m_Vsync;		
	
	public: 
		Window(int width, int height, const char* title, bool fullscreen, bool vsync);
		~Window();
		
		void setTitle(const char* title);
		void setSize(int width, int height);

		bool isClosing() const;
		void close() const;

		static bool resized;

		int getWidth();
		int getHeight();
		GLFWwindow* getWindow() const;

		void setVsync(bool enabled);
		bool isVsync() const;

		static void window_resize_callback(GLFWwindow* window, int width, int height);

		void swapBuffers() const;

	private: 
		bool Init();

	};

}