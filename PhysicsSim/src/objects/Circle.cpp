#include "Circle.h"
#include "utils/GlfwAndDebugIncludes.h"

#include <cmath>
#include <vector>

namespace Object
{
	struct Circle::CircleImpl
	{
		//Deleted constructors
		CircleImpl() = delete;
		CircleImpl(const CircleImpl& other) = delete;
		CircleImpl& operator=(const CircleImpl& other) = delete;
		CircleImpl(const CircleImpl&& other) = delete;
		CircleImpl& operator=(const CircleImpl&& other) = delete;

		//Custom constructors
		CircleImpl(const float r);

		//Default constructors/destructor
		~CircleImpl();

		//Member methods

		//Member variables
		float radius;
	};

	Circle::CircleImpl::CircleImpl(const float r) :
		radius(r)
	{}

	Circle::CircleImpl::~CircleImpl() = default;

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
		const int numVertices = 100;
		const float angle = 2.0f * 3.14159f / numVertices;
		for (int i = 0; i < numVertices; i++)
		{
			const float x = r * cosf(i * angle);
			const float y = r * sinf(i * angle);
			vertices.push_back(glm::vec2(x, y));
		}

		SetVertices(vertices);
	}

	Circle::Circle() = default;
	Circle::~Circle() = default;

	float Circle::GetRadius() const
	{
		return _impl->radius;
	}
}