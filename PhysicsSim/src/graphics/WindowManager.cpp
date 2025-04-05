/**
* @file WindowManager.cpp
* @brief
* Function definitions for the WindowManager class. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "WindowManager.hpp"

#include "utils/GlfwIncludes.hpp"

/// @brief Scene namespace
namespace Scene
{
	/// @brief WindowManager PIMPL implementation structure.
	struct WindowManager::WindowManagerImpl
	{
		//Deleted constructors

		/// @brief Deleted default constructor.
		WindowManagerImpl() = delete;
		/// @brief Deleted copy constructor.
		WindowManagerImpl(const WindowManagerImpl& other) = delete;
		/// @brief Deleted copy assignment operator.
		WindowManagerImpl& operator=(const WindowManagerImpl& other) = delete;
		/// @brief Deleted move constructor.
		WindowManagerImpl(const WindowManagerImpl&& other) = delete;
		/// @brief Deleted move assignment operator.
		WindowManagerImpl& operator=(const WindowManagerImpl&& other) = delete;

		//Custom constructors

		/**
		* @brief Custom constructor for the WindowManagerImpl class.
		* @param name The name of the window.
		* @param width The width of the window.
		* @param height The height of the window.
		*/
		WindowManagerImpl(const std::string& name, const int& width, const int& height);

		//Default constructors/destructor

		/// @brief Destructor.
		~WindowManagerImpl();

		//Member methods

		//Member variables

		/// @brief Name of the window.
		std::string name;
		/// @brief GLSL version.
		const char* glsl_version = nullptr;
		/// @brief Pointer to the window handle.
		GLFWwindow* window = nullptr;
		/// @brief Width of the window.
		int width;
		/// @brief Height of the window.
		int height;
	};

	/**
	* @details
	* Custom constructor for the WindowManagerImpl class. Sets the name, width,
	* and height of the window. Initializes OpenGL and creates the window. 
	*/
	WindowManager::WindowManagerImpl::WindowManagerImpl(
		const std::string& name,
		const int& width,
		const int& height) :
		name(name),
		width(width),
		height(height)
	{
		if (!glfwInit())
		{
			glfwTerminate();
			return;
		}

		glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		window = glfwCreateWindow(this->width, this->height, this->name.c_str(), nullptr, nullptr);

		if (window == nullptr) return;

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, GLFWFramebufferSizeCallback);
		glfwSetErrorCallback(GLFWErrorCallback);
		glfwSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			return;
		}
	}

	/**
	* @details
	* WindowManagerImpl destructor. Destroys the window and terminates OpenGL.
	*/
	WindowManager::WindowManagerImpl::~WindowManagerImpl()
	{
		glfwDestroyWindow(window);
		glfwTerminate();

		window = nullptr;
		glsl_version = nullptr;
	}

	/**
	* @details
	* Default constructor.
	*/
	WindowManager::WindowManager() = default;

	/**
	* @details
	* Default destructor.
	*/
	WindowManager::~WindowManager() = default;

	/**
	* @details
	* Custom constructor for the WindowManager class. Passes the name, width, and
	* height to the PIMPL implementation.
	*/
	WindowManager::WindowManager(
		const std::string& name,
		const int& width, const
		int& height) :
		_impl(std::make_unique<WindowManagerImpl>(name, width, height))
	{}

	/**
	* @details
	* Get the pointer to the window handle.
	*/
	GLFWwindow* WindowManager::GetWindow() const
	{
		return _impl->window;
	}

	/**
	* @details
	* Get the window size as a pair of ints.
	*/
	std::pair<int, int> WindowManager::GetWindowSize() const
	{
		return std::pair<int, int>(_impl->width, _impl->height);
	}

	/**
	* @details
	* Get the GLSL version.
	*/
	const char* WindowManager::GetGlslVersion() const
	{
		return _impl->glsl_version;
	}

	/**
	* @details
	* Get whether the window should close from OpenGL.
	*/
	bool WindowManager::ShouldClose() const
	{
		return glfwWindowShouldClose(_impl->window);
	}

	/**
	* @details
	* Swap the buffers in OpenGL.
	*/
	void WindowManager::SwapBuffers()
	{
		glfwSwapBuffers(_impl->window);
	}

	/**
	* @details
	* OpenGL frame buffer callback function. Sets the viewport to the new width
	* and height.
	*/
	void WindowManager::GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	};

	/**
	* @details
	* OpenGL error callback function. Logs the error with spdlog.
	*/
	void WindowManager::GLFWErrorCallback(int error, const char* description)
	{
		//DebugMessage("GLFW Error " + std::to_string(error) + ": " + std::string(description), __func__);
	};
}