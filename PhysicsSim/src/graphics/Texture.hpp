/**
* @file Texture.hpp
* @brief
* Function declarations to create and manage textures. Uses the PIMPL idiom to hide
* implementation details.
*/

#pragma once

#ifndef _TEXTURE_
#define _TEXTURE_

#include <memory>
#include <vector>

//External forward declarations

//Internal declarations

/// @brief Scene namespace
namespace Graphics
{
	//External forward declarations

	//Internal declarations

	/// @brief Texture class
	class Texture
	{
	public:
		//Deleted constructors

		/// @brief Deleted copy constructor.
		Texture(const Texture& other) = delete;
		/// @brief Deleted copy assignment operator.
		Texture& operator=(const Texture& other) = delete;
		/// @brief Deleted move constructor.
		Texture(Texture&& other) = delete;
		/// @brief Deleted move assignment operator.
		Texture& operator=(const Texture&& other) = delete;

		//Custom constructors

		/**
		* @brief Custom constructor for the Texture class.
		* @param width The width of the texture.
		* @param height The height of the texture.
		*/
		Texture(const int& width, const int& height);

		//Default constructors/destructor

		/// @brief Default constructor.
		Texture();
		/// @brief Default destructor.
		~Texture();

		//Member methods

		/**
		* @brief Get the texture error status.
		* @return True if there is an error, false otherwise.
		*/
		bool GetErrorStatus() const;

		/**
		* @brief Get the OpenGL texture ID.
		* @return The OpenGL texture ID.
		*/
		unsigned int& GetTextureId();

		/// @brief Render the texture.
		void Render();

		/**
		* @brief Setup the framebuffer and texture.
		* @param width The width of the texture.
		* @param height The height of the texture.
		*/
		void SetupFramebufferAndTexture(const int& width, const int& height);
		
		/**
		* @brief Get the aspect ratio of the texture.
		* @return The aspect ratio of the texture.
		*/
		float GetAspectRatio() const;

		//PIMPL idiom
	private:
		/// @brief Forward declaration of TextureImpl struct.
		struct TextureImpl;
		/// @brief Class member variable to hold the implementation details.
		std::unique_ptr<TextureImpl> _impl;
	};
}

#endif