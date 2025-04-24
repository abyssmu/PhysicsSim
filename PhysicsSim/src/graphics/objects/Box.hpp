/**
* @file Box.hpp
* @brief
* Function declarations for the Box class. Uses the PIMPL idiom to hide
* implementation details.
*/

#pragma once

#ifndef _BOX_
#define _BOX_

#include "Object.hpp"

#include <glm/glm.hpp>
#include <memory>

//External forward declarations

//Internal declarations

/// @brief Object namespace
namespace Object
{
	//External forward declarations

	//Internal declarations

	/// @brief Box class. Inherits from public Object.
	class Box : public Object
	{
	public:
		//Deleted constructors

		/// @brief Deleted copy constructor.
		Box(const Box& other) = delete;
		/// @brief Deleted copy assignment operator.
		Box& operator=(const Box& other) = delete;
		/// @brief Deleted move constructor.
		Box(const Box&& other) = delete;
		/// @brief Deleted move assignment operator.
		Box& operator=(const Box&& other) = delete;

		//Custom constructors

		/**
		* @brief Custom constructor for the Box class.
		* @param center_x The x-coordinate of the center of the box.
		* @param center_y The y-coordinate of the center of the box.
		* @param box_width_perc The width of the box as a percentage of the window.
		* @param box_height_perc The height of the box as a percentage of the window.
		* @param max_width The maximum width of the window.
		* @param max_height The maximum height of the window.
		*/
		Box(
			const int center_x,
			const int center_y,
			const int box_width_perc,
			const int box_height_perc,
			const int max_width,
			const int max_height);

		//Default constructors/destructor

		/// @brief Default constructor.
		Box();

		/// @brief Default destructor.
		~Box();

		//Member methods

		//PIMPL idiom
	private:
		/// @brief Forward declaration of BoxImpl struct.
		struct BoxImpl;
		/// @brief Class member to hold the implementation details.
		std::unique_ptr<BoxImpl> _impl;
	};
}

#endif