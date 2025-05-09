/**
* @file Box.hpp
* @brief
* Function declarations for the Box class. Uses the PIMPL idiom to hide
* implementation details.
*/

#pragma once

#ifndef _BOX_
#define _BOX_

#include <memory>

//External forward declarations

//Internal declarations

/// @brief Object namespace
namespace Object
{
	//External forward declarations

	//Internal declarations

	/// @brief Box class
	class Box
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
		* @param box_width_perc The width of the box as a percentage of the window width.
		* @param box_height_perc The height of the box as a percentage of the window height.
		* @param window_width The width of the window.
		* @param window_height The height of the window.
		* @param red The red color value of the box.
		* @param green The green color value of the box.
		* @param blue The blue color value of the box.
		*/
		Box(
			const int box_width_perc,
			const int box_height_perc,
			const int window_width,
			const int window_height,
			const float red,
			const float green,
			const float blue);

		//Default constructors/destructor

		/// @brief Default constructor.
		Box();

		/// @brief Default destructor.
		~Box();

		//Member methods
		
		/**
		* @brief Draw the box.
		* @param shader The ID of the shader program to use for rendering.
		*/
		void Draw(const unsigned int shader);

		//PIMPL idiom
	private:
		/// @brief Forward declaration of BoxImpl struct.
		struct BoxImpl;
		/// @brief Class member to hold the implementation details.
		std::unique_ptr<BoxImpl> _impl;
	};
}

#endif