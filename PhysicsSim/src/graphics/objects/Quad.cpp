/**
* @file Quad.cpp
* @brief
* Function definitions for the Quad. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "Quad.hpp"

/// @brief Object namespace
namespace Object
{
	/// @brief Quad PIMPL implementation structure.
	struct Quad::QuadImpl
	{
		//Deleted constructors

		/// @brief Deleted copy constructor.
		QuadImpl(const QuadImpl& other) = delete;
		/// @brief Deleted copy assignment operator.
		QuadImpl& operator=(const QuadImpl& other) = delete;
		/// @brief Deleted move constructor.
		QuadImpl(const QuadImpl&& other) = delete;
		/// @brief Deleted move assignment operator.
		QuadImpl& operator=(const QuadImpl&& other) = delete;

		//Custom constructors

		//Default constructors/destructor

		/// @brief Default constructor.
		QuadImpl() = default;
		/// @brief Default destructor.
		~QuadImpl() = default;

		//Member methods

		//Member variables

		/// @brief Width of the quad.
		float width;
		/// @brief Height of the quad.
		float height;
	};

	/**
	* @details
	* Custom constructor for the Quad class. Initializes the Object parent class
	* to position (center_x, center_y, 0) and color (red, green, blue). Converts
	* the width and height to NDC space. Sets the width and height of the PIMPL
	* implementation.
	*/
	Quad::Quad(
		const float center_x,
		const float center_y,
		const int width,
		const int height,
		const int screen_width,
		const int screen_height,
		const float red,
		const float green,
		const float blue) :
		Object(center_x, center_y, 0.0f, red, green, blue),
		_impl(std::make_unique<QuadImpl>())
	{
		const float aspect_ratio = static_cast<float>(screen_width) / screen_height;
		_impl->width = static_cast<float>(width) / (screen_width / 2.0f);
		_impl->height =
			static_cast<float>(height) / (screen_height / 2.0f) / aspect_ratio;
		float half_width = static_cast<float>(_impl->width) / 2.0f;
		float half_height = static_cast<float>(_impl->height) / 2.0f;

		// Calculate the four vertices of the quad
		glm::vec2 top_left = { center_x - half_width, center_y + half_height };
		glm::vec2 top_right = { center_x + half_width, center_y + half_height };
		glm::vec2 bottom_left = { center_x - half_width, center_y - half_height };
		glm::vec2 bottom_right = { center_x + half_width, center_y - half_height };

		// Store the vertices in a vector and set the vertices in the parent class
		std::vector<glm::vec2> vertices =
			{ top_left, top_right, bottom_right, bottom_left };
		SetVertices(vertices);
	}

	/**
	* @details
	* Default constructor for the Quad class.
	*/
	Quad::Quad() = default;

	/**
	* @details
	* Default destructor for the Quad class.
	*/
	Quad::~Quad() = default;
}