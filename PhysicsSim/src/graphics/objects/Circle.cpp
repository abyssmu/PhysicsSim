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
	* to the PIMPL implementation. Radius is defined in NDC coordinates (in terms
	* of the width) and ranges from [-1, 1]. The number of vertices is determined
	* based on the radius.
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
		* Determine the number of vertices based on the radius. Scales linearly
		* between the max and min number of vertices according to a piecewise
		* function:
		* min_r for r <= min_r
		* ((1 / (max_r - min_r)) * (r - min_r)) * (max_verts - min_verts) + min_verts
		* for min_r < r < max_r
		* max_r for r >= max_r
		*/
		const float max_num_vertices = 30.0f;
		const float min_num_vertices = 5.0f;
		const float min_r = 0.005f;
		const float max_r = 0.15f;
		int num_vertices = 0;

		if (r <= min_r) num_vertices = min_num_vertices;
		else if (r >= max_r) num_vertices = max_num_vertices;
		else
		{
			num_vertices = static_cast<int>(
				((1.0f / (max_r - min_r)) * (r - min_r)) *
				(max_num_vertices - min_num_vertices) + min_num_vertices);
		}

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