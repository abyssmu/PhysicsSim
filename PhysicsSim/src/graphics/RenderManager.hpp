/**
* @file RenderManager.hpp
* @brief
* Function declarations for the RenderManager class. Uses the PIMPL idiom to hide
* implementation details.
*/

#pragma once

#ifndef _RENDERMANAGER_
#define _RENDERMANAGER_

#include <memory>
#include <vector>

//External forward declarations

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
	/// @brief Forward declaration of Shader class.
	class Shader;

	//Internal declarations

	/// @brief RenderManager class
	class RenderManager
	{
	public:
		//Deleted constructors

		/// @brief Deleted copy constructor.
		RenderManager(const RenderManager& other) = delete;
		/// @brief Deleted copy assignment operator.
		RenderManager& operator=(const RenderManager& other) = delete;
		/// @brief Deleted move constructor.
		RenderManager(RenderManager&& other) = delete;
		/// @brief Deleted move assignment operator.
		RenderManager& operator=(const RenderManager&& other) = delete;

		//Custom constructors
		/**
		* @brief Custom constructor for the RenderManager class.
		* @param width The width of the texture.
		* @param height The height of the texture.
		*/
		RenderManager(const int& width, const int& height);

		//Default constructors/destructor

		/// @brief Default constructor.
		RenderManager();
		/// @brief Default destructor
		~RenderManager();

		//Member methods

		/**
		* @brief Render the texture for the ImGui render window.
		* @param objects The objects to render to the texture.
		* @param box_height_perc The height of the simulation box as a percentage of the window.
		* @param box_width_perc The width of the simulation box as a percentage of the window.
		*/
		void RenderTexture(
			std::vector<std::shared_ptr<Object::Object>>& objects,
			const int box_height_perc,
			const int box_width_perc);
		/**
		* @brief Get the texture for the RenderManager.
		* @return The texture for the RenderManager.
		*/
		std::shared_ptr<Texture> GetTexture();
		/**
		* @brief Get the aspect ratio of the texture.
		* @return The aspect ratio of the texture.
		*/
		float GetTextureAspectRatio() const;

		//PIMPL idiom
	private:
		/// @brief Forward declaration of RenderManagerImpl struct.
		struct RenderManagerImpl;
		/// @brief Class member variable to hold the implementation details.
		std::unique_ptr<RenderManagerImpl> _impl;
	};
}

#endif