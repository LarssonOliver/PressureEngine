#include "Window.h"
#include "../Input/Input.h"

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
		if (fullscreen) {
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, vidmode->width, vidmode->height, vidmode->refreshRate);
			width = vidmode->width;
			height = vidmode->height;
		}
		glfwSetWindowPos(window, vidmode->width / 2 - width / 2, vidmode->height / 2 - height / 2);

		glfwMakeContextCurrent(window);
		glfwSwapInterval(vsync);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSetWindowSizeCallback(window, window_resize_callback);

		glfwSetKeyCallback(window, Keyboard::key_callback);
		glfwSetMouseButtonCallback(window, Mouse::mouse_button_callback);
		glfwSetScrollCallback(window, Mouse::mouse_scroll_callback);
		glfwSetCursorPosCallback(window, Mouse::mouse_pos_callback); 


		glfwShowWindow(window);

		return true;
	}

	bool Window::resized = false;

	void Window::window_resize_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		resized = true;
	}

	void Window::tick() {
		// Implement key callbacks here?
	}

	void Window::setTitle(const char* title) {
		this->title = title;
		glfwSetWindowTitle(window, title);
	}

	void Window::setSize(int width, int height) {
		glfwSetWindowSize(window, width, height);
		this->width = width;
		this->height = height;
	}

	int Window::getWidth() {
		glfwGetWindowSize(window, &width, &height);
		return width;
	}

	int Window::getHeight() {
		glfwGetWindowSize(window, &width, &height);
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