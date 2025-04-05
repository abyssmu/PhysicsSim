/**
* @file Circle.hpp
* @details
* Function declarations for the Circle class. Uses the PIMPL idiom to hide
* implementation details.
*/

#pragma once

#ifndef _CIRCLE_
#define _CIRCLE_

#include "Object.hpp"

#include <glm/glm.hpp>
#include <memory>

//External forward declarations

/// @brief Forward declaration of GLuint.
typedef unsigned int GLuint;

//Internal declarations

/// @brief Object namespace
namespace Object
{
	//External forward declarations

	/// @brief Forward declaration of ObjectImpl from Object class.
	struct Object::ObjectImpl;

	//Internal declarations

	/// @brief Circle class. Inherits from public Object.
	class Circle : public Object
	{
	public:
		//Deleted constructors

		/// @brief Deleted copy constructor.
		Circle(const Circle& other) = delete;
		/// @brief Deleted copy assignment operator.
		Circle& operator=(const Circle& other) = delete;
		/// @brief Deleted move constructor.
		Circle(const Circle&& other) = delete;
		/// @brief Deleted move assignment operator.
		Circle& operator=(const Circle&& other) = delete;

		//Custom constructors
		
		/**
		* @brief Constructor for the Circle class.
		* @param r The radius of the circle.
		* @param x The x-coordinate of the circle.
		* @param y The y-coordinate of the circle.
		* @param z The z-coordinate of the circle.
		* @param red The red color value of the circle.
		* @param green The green color value of the circle.
		* @param blue The blue color value of the circle.
		*/
		Circle(
			const float r,
			const float x,
			const float y,
			const float z,
			const float red,
			const float green,
			const float blue);

		//Default constructors/destructor

		/// @brief Default constructor.
		Circle();
		/// @brief Default destructor.
		~Circle();

		//Member methods

		/**
		* @brief Get the radius of the circle.
		* @return The radius of the circle.
		*/
		float GetRadius() const;

		//PIMPL idiom
	private:
		/// @brief Forward declaration of CircleImpl.
		struct CircleImpl;
		/// @brief Class member variable to hold the implementation details.
		std::unique_ptr<CircleImpl> _impl;
	};
}

#endif