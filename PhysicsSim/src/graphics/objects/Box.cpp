/**
* @file Box.cpp
* @brief
* Function definitions for the Box class. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "Box.hpp"
#include "Quad.hpp"

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

		/**
		* @brief Custom constructor for the BoxImpl class.
		* @param box_width_perc The width of the box as a percentage of the window width.
		* @param box_height_perc The height of the box as a percentage of the window height.
		* @param window_width The width of the window.
		* @param window_height The height of the window.
		* @param red The red color value of the box.
		* @param green The green color value of the box.
		* @param blue The blue color value of the box.
		*/
		BoxImpl(
			const int box_width_perc,
			const int box_height_perc,
			const int window_width,
			const int window_height,
			const float red,
			const float green,
			const float blue);

		//Default constructors/destructor

		/// @brief Default destructor.
		~BoxImpl() = default;

		//Member methods

		//Member variables

		/// @brief The width of the box.
		int width = 0;
		/// @brief The height of the box.
		int height = 0;
		/// @brief Quad object to represent the left side of the box.
		std::unique_ptr<Quad> left_side;
		/// @brief Quad object to represent the right side of the box.
		std::unique_ptr<Quad> right_side;
		/// @brief Quad object to represent the top side of the box.
		std::unique_ptr<Quad> top_side;
		/// @brief Quad object to represent the bottom side of the box.
		std::unique_ptr<Quad> bottom_side;
	};

	/**
	* @details
	* Custom constructor for the BoxImpl class. Calculates the four vertices of
	* the box using the width and height and passes them to the four Quad objects
	* to create the four sides of the box.
	*/
	Box::BoxImpl::BoxImpl(
		const int box_width_perc,
		const int box_height_perc,
		const int window_width,
		const int window_height,
		const float red,
		const float green,
		const float blue)
	{
		// Calculate the width and height of the box
		width = box_width_perc * window_width;
		height = box_height_perc * window_height;

		// Initialize each side of the box with their centers
		float half_width = static_cast<float>(width) / 2.0f;
		float half_height = static_cast<float>(height) / 2.0f;

		left_side =
			std::make_unique<Quad>(
				-half_width, 0.0f,  // Center x, center y
				width, height,
				window_width, window_height,
				red, green, blue);
		right_side =
			std::make_unique<Quad>(
				half_width, 0.0f,  // Center x, center y
				width, height,
				window_width, window_height,
				red, green, blue);
		top_side =
			std::make_unique<Quad>(
				0.0f, half_height,  // Center x, center y
				width, height,
				window_width, window_height,
				red, green, blue);
		bottom_side =
			std::make_unique<Quad>(
				0.0f, -half_height,  // Center x, center y
				width, height,
				window_width, window_height,
				red, green, blue);
	}

	/**
	* @details
	* Custom constructor for the Box class. Passes the parameters to the PIMPL
	* implementation.
	*/
	Box::Box(
		const int box_width_perc,
		const int box_height_perc,
		const int window_width,
		const int window_height,
		const float red,
		const float green,
		const float blue) :
		_impl(
			std::make_unique<BoxImpl>(
				box_width_perc,
				box_height_perc,
				window_width,
				window_height,
				red,
				green,
				blue))
	{}

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

	/**
	* @details
	* Draw the box using the shader ID. Draws each side of the box.
	*/
	void Box::Draw(const unsigned int shader)
	{
		_impl->left_side->Draw(shader);
		_impl->right_side->Draw(shader);
		_impl->top_side->Draw(shader);
		_impl->bottom_side->Draw(shader);
	}
}