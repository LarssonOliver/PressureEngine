#include "Window.h"
#include "../Input/Input.h"

namespace Pressure {

	Window::Window(int width, int height, const char* title, bool fullscreen, bool vsync)
		: m_Width(width), m_Height(height), m_Title(title), m_Fullscreen(fullscreen), m_Vsync(vsync) {
		if (!Init()) {
			
		}
	}

	Window::~Window() {
		glfwSetWindowShouldClose(m_Window, true);
		glfwDestroyWindow(m_Window);
	}

	bool Window::Init() {
		glfwDefaultWindowHints();

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window) {
			return false;
		}

		const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		if (m_Fullscreen) {
			glfwSetWindowMonitor(m_Window, glfwGetPrimaryMonitor(), 0, 0, vidmode->width, vidmode->height, vidmode->refreshRate);
			m_Width = vidmode->width;
			m_Height = vidmode->height;
		}
		glfwSetWindowPos(m_Window, vidmode->width / 2 - m_Width / 2, vidmode->height / 2 - m_Height / 2);

		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(m_Vsync);

		glViewport(0, 0, m_Width, m_Height);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSetWindowSizeCallback(m_Window, window_resize_callback);

		glfwSetKeyCallback(m_Window, Keyboard::key_callback);
		glfwSetMouseButtonCallback(m_Window, Mouse::mouse_button_callback);
		glfwSetScrollCallback(m_Window, Mouse::mouse_scroll_callback);
		glfwSetCursorPosCallback(m_Window, Mouse::mouse_pos_callback); 


		glfwShowWindow(m_Window);

		return true;
	}

	bool Window::resized = false;

	void Window::window_resize_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		resized = true;
	}

	void Window::swapBuffers() const {
		glfwSwapBuffers(m_Window);
	}

	//void Window::tick() {
	//	// Implement key callbacks here?
	//}

	void Window::setTitle(const char* title) {
		this->m_Title = title;
		glfwSetWindowTitle(m_Window, title);
	}

	void Window::setSize(int width, int height) {
		glfwSetWindowSize(m_Window, width, height);
		this->m_Width = width;
		this->m_Height = height;
	}

	bool Window::isClosing() const {
		return glfwWindowShouldClose(m_Window);
	}

	void Window::close() const {
		glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
	}

	int Window::getWidth() {
		glfwGetWindowSize(m_Window, &m_Width, &m_Height);
		return m_Width;
	}

	int Window::getHeight() {
		glfwGetWindowSize(m_Window, &m_Width, &m_Height);
		return m_Height;
	}

	GLFWwindow* Window::getWindow() const {
		return m_Window;
	}

	void Window::setVsync(bool enabled) {
		m_Vsync = enabled;
		glfwSwapInterval(enabled);
	}

	bool Window::isVsync() const {
		return m_Vsync;
	}

}