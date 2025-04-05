/**
* @file Scene.hpp
* @brief
* Function declarations to create and manage the scene. Uses the PIMPL idiom to
* hide implementation details. Based on the OpenGL tutorial at:
* https://learnopengl.com/Getting-started/OpenGL
*/

#pragma once

#ifndef _SCENE_
#define _SCENE_

#include <memory>
#include <string>
#include <vector>

//External forward declarations

/// @brief Forward declaration of GLFWwindow.
struct GLFWwindow;

/// @brief Forward declaration of Object namespace.
namespace Object
{
	/// @brief Forward declaration of Object class in Object namespace.
	class Object;
}

//Internal declarations

/// @brief Scene namespace
namespace Scene
{
	//External forward declarations

	/// @brief Forward declaration of Texture class.
	class Texture;
	
	//Internal declarations

	/// @brief Scene class
	class Scene
	{
	public:
		//Deleted constructors

		/// @brief Deleted copy constructor.
		Scene(const Scene& other) = delete;
		/// @brief Deleted copy assignment operator.
		Scene& operator=(const Scene& other) = delete;
		/// @brief Deleted move constructor.
		Scene(Scene&& other) = delete;
		/// @brief Deleted move assignment operator.
		Scene& operator=(const Scene&& other) = delete;

		//Custom constructors

		/**
		* @brief Custom constructor for the Scene class.
		* @param name The name of the scene.
		* @param width The width of the scene window.
		* @param height The height of the scene window.
		*/
		Scene(const std::string& name, const int& width, const int& height);

		//Default constructors/destructor

		/// @brief Default constructor.
		Scene();
		/// @brief Default destructor.
		~Scene();

		//Member methods

		/**
		* @brief Render the texture for the ImGui render window.
		* @param objects The vector of objects to render.
		* @param box_height_perc The height of the box as a percentage of the window.
		* @param box_width_perc The width of the box as a percentage of the window.
		*/
		void RenderTexture(
			std::vector<std::shared_ptr<Object::Object>>& objects,
			const int box_height_perc,
			const int box_width_perc);

		/**
		* @brief Render the scene with the specified color.
		* @param r The red color value.
		* @param g The green color value.
		* @param b The blue color value.
		* @param a The alpha color value.
		*/
		void Render(const float& r, const float& g, const float& b, const float& a);
		
		/**
		* @brief Get the GLSL version.
		* @return The GLSL version.
		*/
		const char* GetGlslVersion() const;

		/**
		* @brief Get the window handle.
		* @return A pointer to the window handle.
		*/
		GLFWwindow* GetWindow() const;

		/**
		* @brief Get the window size.
		* @return The window size.
		*/
		std::pair<int, int> GetWindowSize() const;

		/**
		* @brief Get the texture.
		* @return A pointer to the texture.
		*/
		std::shared_ptr<Texture> GetTexture() const;

		/**
		* @brief Get the texture aspect ratio.
		* @return The texture aspect ratio.
		*/
		float GetTextureAspectRatio() const;

		/**
		* @brief Check if the window should close.
		* @return True if the window should close, false otherwise.
		*/
		bool WindowShouldClose() const;

		/// @brief Swap the buffers.
		void SwapBuffers() const;

		//PIMPL idiom
	private:
		/// @brief Forward declaration of SceneImpl struct.
		struct SceneImpl;
		/// @brief Class member variable to hold the implementation details.
		std::unique_ptr<SceneImpl> _impl;
	};
}

#endif