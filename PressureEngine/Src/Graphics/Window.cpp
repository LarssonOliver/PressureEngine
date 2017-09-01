#include "Window.h"
#include "../Callbacks.h"

namespace Pressure {

	Window::Window(int width, int height, const char* title, bool fullscreen, bool vsync)
		: width(width), height(height), title(title), fullscreen(fullscreen), vsync(vsync) {
		if (!Init()) {
			
		}
	}

	Window::~Window() {
		glfwSetWindowShouldClose(window, true);
		glfwDestroyWindow(window);
	}

	bool Window::Init() {
		glfwDefaultWindowHints();

		window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (!window) {
			return false;
		}
		
		const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowPos(window, vidmode->width / 2 - width / 2, vidmode->height / 2 - height / 2);

		glfwMakeContextCurrent(window);
		glfwSwapInterval(vsync);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSetWindowSizeCallback(window, window_resize_callback);
		glfwSetKeyCallback(window, Callbacks::key_callback);

		glfwShowWindow(window);

		return true;
	}

	void Window::window_resize_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	void Window::tick() {
		// Implement key callbacks here?
	}

	void Window::setTitle(const char* title) {
		this->title = title;
		glfwSetWindowTitle(window, title);
	}

	int Window::getWidth() const {
		return width;
	}

	int Window::getHeight() const {
		return height;
	}

	GLFWwindow* Window::getWindow() const {
		return window;
	}

	void Window::setVsync(bool enabled) {
		vsync = enabled;
		glfwSwapInterval(enabled);
	}

	bool Window::isVsync() const {
		return vsync;
	}

}