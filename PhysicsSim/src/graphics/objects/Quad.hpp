/**
* @file Quad.hpp
* @brief
* Function declarations for the Quad class. Uses the PIMPL idiom to hide
* implementation details.
*/

#pragma once

#ifndef _QUAD_
#define _QUAD_

#include "Object.hpp"

#include <memory>

//External forward declarations

//Internal declarations

/// @brief Object namespace
namespace Object
{
	//External forward declarations

	//Internal declarations

	/// @brief Quad class. Inherits from public Object class.
	class Quad : public Object
	{
	public:
		//Deleted constructors

		/// @brief Deleted copy constructor.
		Quad(const Quad& other) = delete;
		/// @brief Deleted copy assignment operator.
		Quad& operator=(const Quad& other) = delete;
		/// @brief Deleted move constructor.
		Quad(const Quad&& other) = delete;
		/// @brief Deleted move assignment operator.
		Quad& operator=(const Quad&& other) = delete;

		//Custom constructors

		/**
		* @brief Custom constructor for the Quad class.
		* @param center_x The x-coordinate of the center of the quad.
		* @param center_y The y-coordinate of the center of the quad.
		* @param width The width of the quad.
		* @param height The height of the quad.
		* @param screen_width The width of the screen.
		* @param screen_height The height of the screen.
		* @param red The red color value of the quad.
		* @param green The green color value of the quad.
		* @param blue The blue color value of the quad.
		*/
		Quad(
			const float center_x,
			const float center_y,
			const int width,
			const int height,
			const int screen_width,
			const int screen_height,
			const float red,
			const float green,
			const float blue);

		//Default constructors/destructor

		/// @brief Constructor
		Quad();
		/// @brief Destructor
		~Quad();

		//Member methods

		//PIMPL idiom
	private:
		/// @brief Forward declaration of QuadImpl struct.
		struct QuadImpl;
		/// @brief Class member variable to hold the implementation details.
		std::unique_ptr<QuadImpl> _impl;
	};
}

#endif