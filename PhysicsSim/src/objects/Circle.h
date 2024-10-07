#pragma once

#ifndef _CIRCLE_
#define _CIRCLE_

#include "Object.h"

#include <glm/glm.hpp>
#include <memory>

//External forward declarations
typedef unsigned int GLuint;

//Internal declarations
namespace Object
{
	//External forward declarations
	struct Object::ObjectImpl;

	//Internal declarations
	class Circle : public Object
	{
	public:
		//Dele	ted constructors
		Circle(const Circle& other) = delete;
		Circle& operator=(const Circle& other) = delete;
		Circle(const Circle&& other) = delete;
		Circle& operator=(const Circle&& other) = delete;

		//Custom constructors
		Circle(
			const float r,
			const float x,
			const float y,
			const float z,
			const float red,
			const float green,
			const float blue);

		//Default constructors/destructor
		Circle();
		~Circle();

		//Member methods
		float GetRadius() const;

		//PIMPL idiom
	private:
		struct CircleImpl;
		std::unique_ptr<CircleImpl> _impl;
	};
}

#endif