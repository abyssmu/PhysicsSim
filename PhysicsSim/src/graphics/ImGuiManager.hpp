/**
* @file ImGuiManager.hpp
* @brief
* Function declarations to initialize and manage the ImGuiManager. Uses the PIMPL
* idiom to hide implementation details.
*/

#pragma once

#ifndef _IMGUIMANAGER_
#define _IMGUIMANAGER_

#include <memory>
#include <string>

//External forward declarations

/// @brief Forward declaration of GLFWwindow.
struct GLFWwindow;
/// @brief Forward declaration of ImVec2.
struct ImVec2;
/// @brief Forward declaration of ImVec4.
struct ImVec4;
/// @brief Forward declaration of Scene namespace.
namespace Scene
{
	/// @brief Forward declaration of Texture class in Scene namespace.
	class Texture;
}

//Internal declarations

/// @brief Application namespace
namespace App
{
	//External forward declarations

	/// @brief Forward declaration of ThermodynamicSimulationVariables struct.
	struct ThermodynamicSimulationVariables;

	//Internal declarations

	/// @brief ImGuiManager class
	class ImGuiManager
	{
	public:
		//Deleted constructors

		/// @brief Deleted copy constructor.
		ImGuiManager(const ImGuiManager& other) = delete;
		/// @brief Deleted copy assignment operator.
		ImGuiManager& operator=(const ImGuiManager& other) = delete;
		/// @brief Deleted move constructor.
		ImGuiManager(const ImGuiManager&& other) = delete;
		/// @brief Deleted move assignment operator.
		ImGuiManager& operator=(const ImGuiManager&& other) = delete;

		//Custom constructors

		/**
		* @brief
		* Custom constructor for the ImGuiManager class.
		* @param clear_color The clear color for the ImGuiManager.
		* @param window The GLFW window to render the ImGuiManager.
		*/
		ImGuiManager(
			ImVec4 clear_color,
			GLFWwindow* window,
			const char* glsl_version);
		
		//Default constructors/destructor

		/// @brief Default constructor.
		ImGuiManager();
		/// @brief Default destructor.
		~ImGuiManager();

		//Member methods

		/// @brief Generate a new frame for ImGui.
		void NewFrame();
		/**
		* @brief
		* Get the background color for the ImGui.
		* @return
		* Background color for the ImGui.
		*/
		ImVec4& GetClearColor();
		/**
		* @brief
		* Get the size of the render window.
		* @return
		* Size of the render window.
		*/
		ImVec2& GetRenderSize();
		/// @brief Render the ImGui draw data.
		void RenderDrawData();
		/// @brief Setup ImGui's demo window.
		void SetupDemoWindow();

		//Application specific methods

		/**
		* @brief
		* Setup simulation window.
		* @param texture The texture to render in the window.
		* @param aspect_ratio The aspect ratio of the window.
		*/
		void SetupWindow(
			std::shared_ptr<Scene::Texture> texture,
			float aspect_ratio);

		//Simulation methods

		/**
		* @brief
		* Check for state change in the ImGuiManager.
		* @return
		* State change type.
		*/
		std::string& CheckForStateChanged();

		/**
		* @brief
		* Get the simulation variables.
		* @return
		* Structure containing the simulation variables.
		*/
		ThermodynamicSimulationVariables GetSimulationVariables();

		//PIMPL idiom
	private:
		/// @brief Forward declaration of ImGuiManagerImpl struct.
		struct ImGuiManagerImpl;
		/// @brief Class member variable to hold the implementation details.
		std::unique_ptr<ImGuiManagerImpl> _impl;
	};
}

#endif