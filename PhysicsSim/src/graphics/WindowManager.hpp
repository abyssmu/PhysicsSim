/**
* @file WindowManager.hpp
* @brief
* Function declarations to initialize and manage the application window. Uses
* the PIMPL idiom to hide implementation details.
*/

#pragma once

#ifndef _WINDOWMANAGER_
#define _WINDOWMANAGER_

#include <memory>
#include <string>

//External forward declarations

/// @brief Forward declaration of GLFWwindow.
struct GLFWwindow;

//Internal declarations

/// @brief Scene namespace
namespace Scene
{
	//External forward declarations

	//Internal declarations

	/// @brief WindowManager class
	class WindowManager
	{
	public:
		//Deleted constructors

		/// @brief Deleted copy constructor.
		WindowManager(const WindowManager& other) = delete;
		/// @brief Deleted copy assignment operator.
		WindowManager& operator=(const WindowManager& other) = delete;
		/// @brief Deleted move constructor.
		WindowManager(WindowManager&& other) = delete;
		/// @brief Deleted move assignment operator.
		WindowManager& operator=(const WindowManager&& other) = delete;

		//Custom constructors

		/**
		* @brief Custom constructor for the WindowManager class.
		* @param name The name of the window.
		* @param width The width of the window.
		* @param height The height of the window.
		*/
		WindowManager(const std::string& name, const int& width, const int& height);

		//Default constructors/destructor

		/// @brief Default constructor.
		WindowManager();

		/// @brief Default destructor.
		~WindowManager();

		//Member methods

		/**
		* @brief Get the pointer to the window handle.
		* @return Pointer to the window handle.
		*/
		GLFWwindow* GetWindow() const;

		/**
		* @brief Get the window size.
		* @return Pair of integers representing the window size.
		*/
		std::pair<int, int> GetWindowSize() const;

		/**
		* @brief Get the GLSL version.
		* @return The GLSL version.
		*/
		const char* GetGlslVersion() const;

		/**
		* @brief Check if the window should close.
		* @return True if the window should close, false otherwise.
		*/
		bool ShouldClose() const;

		/// @brief Swap the buffers for the window.
		void SwapBuffers();

		/**
		* @brief Set the window size in OpenGL.
		* @param window The window handle.
		* @param width The width of the window.
		* @param height The height of the window.
		*/
		static void GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height);

		/**
		* @brief Callback function for GLFW error handling.
		* @param error The error code.
		* @param description The error description.
		*/
		static void GLFWErrorCallback(int error, const char* description);

		//PIMPL idiom
	private:
		/// @brief Forward declaration of WindowManagerImpl.
		struct WindowManagerImpl;
		/// @brief Class member variable to hold the implementation details.
		std::unique_ptr<WindowManagerImpl> _impl;
	};
}

#endif