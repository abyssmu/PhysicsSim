#include "Scene.h"

namespace Scene
{
	WindowManager::WindowManager(const string& name, const int& width, const int& height) :
		_name(name), _width(width), _height(height)
	{
		if (!glfwInit())
		{
			glfwTerminate();
			return;
		}

		_glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		_window = glfwCreateWindow(_width, _height, _name.c_str(), nullptr, nullptr);

		if (_window == nullptr) return;

		glfwMakeContextCurrent(_window);
		glfwSetFramebufferSizeCallback(_window, GLFWFramebufferSizeCallback);
		glfwSetErrorCallback(GLFWErrorCallback);
		glfwSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			return;
		}
	}

	void WindowManager::Terminate()
	{
		glfwDestroyWindow(_window);

		_window = nullptr;
		_glsl_version = nullptr;
	}

	GLFWwindow* WindowManager::GetWindow() const
	{
		return _window;
	}

	const char* WindowManager::GetGlslVersion() const
	{
		return _glsl_version;
	}

	bool WindowManager::ShouldClose() const
	{
		return glfwWindowShouldClose(_window);
	}

	void WindowManager::SwapBuffers()
	{
		glfwSwapBuffers(_window);
	}
}