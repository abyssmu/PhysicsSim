/**
* @file Box.cpp
* @brief
* Function definitions for the Box class. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "Box.hpp"
#include "utils/GlfwIncludes.hpp"

/// @brief Object namespace
namespace Object
{
	/// @brief Box PIMPL implementation structure.
	struct Box::BoxImpl
	{
		//Deleted constructors

		/// @brief Deleted default constructor.
		BoxImpl() = delete;
		/// @brief Deleted copy constructor.
		BoxImpl(const BoxImpl& other) = delete;
		/// @brief Deleted copy assignment operator.
		BoxImpl& operator=(const BoxImpl& other) = delete;
		/// @brief Deleted move constructor.
		BoxImpl(const BoxImpl&& other) = delete;
		/// @brief Deleted move assignment operator.
		BoxImpl& operator=(const BoxImpl&& other) = delete;

		//Custom constructors

		//Default constructors/destructor

		/// @brief Default destructor.
		~BoxImpl() = default;

		//Member methods

		//Member variables
	};

	/**
	* @details
	* Custom constructor for the Box class. WORK IN PROGRESS
	*/
	Box::Box(
		const int center_x,
		const int center_y,
		const int box_width_perc,
		const int box_height_perc,
		const int max_width,
		const int max_height)
	{

	}

	/**
	* @details
	* Default constructor.
	*/
	Box::Box() = default;

	/**
	* @details
	* Default destructor.
	*/
	Box::~Box() = default;
}