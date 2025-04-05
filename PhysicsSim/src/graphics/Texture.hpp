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

/// @brief Forward declaration of GLuint.
typedef unsigned int GLuint;

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
		* @brief Get the OpenGL texture ID.
		* @return The OpenGL texture ID.
		*/
		GLuint& GetTextureId();

		/**
		* @brief Render the texture.
		* @param shader The shader to use for rendering.
		* @param objects A vector of objects to render to the texture.
		* @param box_height_perc The height of the bounding box as a percentage of the window.
		* @param box_width_perc The width of the bounding box as a percentage of the window.
		*/
		void Render(
			GLuint& shader,
			std::vector<std::shared_ptr<Object::Object>>& objects,
			const int box_height_perc,
			const int box_width_perc);

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