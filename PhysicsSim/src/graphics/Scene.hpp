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

//Internal declarations

/// @brief Scene namespace
namespace Graphics
{
	//External forward declarations
	
	//Internal declarations

	/// @brief Basic vertex shader for testing.
	static const std::string BASE_VS_PATH =
		"src/graphics/shaders/BaseVertexShader.vs";
	/// @brief Basic fragment shader for testing.
	static const std::string BASE_FS_PATH =
		"src/graphics/shaders/BaseFragmentShader.fs";

	/// @brief Simulation types enumeration
	enum SimulationTypes
	{
		THERMODYNAMICS
	};

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
		* @param bg_color The background color of the scene.
		*/
		Scene(
			const std::string& name,
			const int& width,
			const int& height,
			const float* bg_color);

		//Default constructors/destructor

		/// @brief Default constructor.
		Scene();
		/// @brief Default destructor.
		~Scene();

		//Member methods

		/**
		* @brief Get the error status of the scene.
		* @return True if there is an error, false otherwise.
		*/
		bool GetErrorStatus() const;

		/**
		* @brief Get the OpenGL shader ID.
		* @return The OpenGL shader ID.
		*/
		unsigned int GetShaderID() const;

		/**
		* @brief Get the texture aspect ratio.
		* @return The texture aspect ratio.
		*/
		float GetTextureAspectRatio() const;

		/**
		* @brief Get the window size.
		* @return The window size.
		*/
		std::pair<int, int> GetWindowSize() const;

		/**
		* @brief Initialize the given simulation render items.
		* @param name The name of the simulation render items.
		* @param particles The vector of particles.
		* @param radius The radius of the particles.
		*/
		void InitializeSimulationRenderItems(
			SimulationTypes type,
			std::vector<float>& particles,
			const float radius);

		/// @brief Poll the OpenGL events and process them.
		void PollEvents();

		/// @brief Render the scene.
		void Render();

		/// @brief Render the simulation items.
		void RenderSimulationItems();

		/// @brief Render the texture for the ImGui render window.
		void RenderTexture();

		/// @brief Swap the buffers.
		void SwapBuffers() const;

		/**
		* @brief Check if the window should close.
		* @return True if the window should close, false otherwise.
		*/
		bool WindowShouldClose() const;

		//PIMPL idiom
	private:
		/// @brief Forward declaration of SceneImpl struct.
		struct SceneImpl;
		/// @brief Class member variable to hold the implementation details.
		std::unique_ptr<SceneImpl> _impl;
	};
}

#endif