/**
* @file Circle.cpp
* @brief
* Function definitions for the Circle class. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "Circle.hpp"
#include "utils/GlfwIncludes.hpp"

#include <cmath>
#include <vector>

/// @brief Object namespace
namespace Object
{
	/// @brief Circle PIMPL implementation structure.
	struct Circle::CircleImpl
	{
		//Deleted constructors

		/// @brief Deleted default constructor.
		CircleImpl() = delete;
		/// @brief Deleted copy constructor.
		CircleImpl(const CircleImpl& other) = delete;
		/// @brief Deleted copy assignment operator.
		CircleImpl& operator=(const CircleImpl& other) = delete;
		/// @brief Deleted move constructor.
		CircleImpl(const CircleImpl&& other) = delete;
		/// @brief Deleted move assignment operator.
		CircleImpl& operator=(const CircleImpl&& other) = delete;

		//Custom constructors

		/**
		* @brief Custom constructor for the CircleImpl class.
		* @param r The radius of the circle.
		*/
		CircleImpl(const float r);

		//Default constructors/destructor

		/// @brief Default destructor.
		~CircleImpl();

		//Member methods

		//Member variables

		/// @brief Radius of the circle.
		float radius;
	};

	/**
	* @details
	* Custom constructor for the CircleImpl class. Initializes the radius of the
	* circle.
	*/
	Circle::CircleImpl::CircleImpl(const float r) :
		radius(r)
	{}

	/**
	* @details
	* Default destructor.
	*/
	Circle::CircleImpl::~CircleImpl() = default;

	/**
	* @details
	* Custom constructor for the circle class. Passes the position (x, y, z) and
	* colors (red, green, blue) to the Object constructor, and passes the radius
	* to the PIMPL implementation.
	*/
	Circle::Circle(
		const float r,
		const float x,
		const float y,
		const float z,
		const float red,
		const float green,
		const float blue) :
		Object(x, y, z, red, green, blue),
		_impl(std::make_unique<CircleImpl>(r))
	{
		std::vector<glm::vec2> vertices;

		/*
		* Determine the number of vertices based on the radius. Essentially scaled
		* by the equation:
		* max - (max - min) * max_r / r
		* Where max_r / r is in (0, 1]. If the number of vertices is less than the
		* minimum, set it to the minimum.
		*/
		const float max_num_vertices = 30.0f;
		const float min_num_vertices = 10.0f;
		const float diff = max_num_vertices - min_num_vertices;
		const float max_radius = 0.10f;
		int num_vertices = int(max_num_vertices - diff * max_radius / r);

		if (num_vertices < min_num_vertices) num_vertices = int(min_num_vertices);

		//Calculate each vertex along the circumference.
		const float angle = 2.0f * 3.14159f / num_vertices;
		for (int i = 0; i < num_vertices; i++)
		{
			const float x = r * cosf(i * angle);
			const float y = r * sinf(i * angle);
			vertices.push_back(glm::vec2(x, y));
		}

		//Set the vertices in the parent class.
		SetVertices(vertices);
	}

	/**
	* @details
	* Default constructor for the Circle class.
	*/
	Circle::Circle() = default;

	/**
	* @details
	* Default destructor for the Circle class.
	*/
	Circle::~Circle() = default;

	/**
	* @details
	* Get the radius of the circle.
	*/
	float Circle::GetRadius() const
	{
		return _impl->radius;
	}
}