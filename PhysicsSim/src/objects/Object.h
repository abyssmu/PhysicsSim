#pragma once

#ifndef _OBJECT_
#define _OBJECT_

#include <glm/glm.hpp>
#include <memory>
#include <vector>

//External forward declarations
typedef unsigned int GLuint;

//Internal declarations
namespace Object
{
	//External forward declarations

	//Internal declarations
	class Object
	{
	public:
		//Deleted constructors
		Object(const Object& other) = delete;
		Object& operator=(const Object& other) = delete;
		Object(const Object&& other) = delete;
		Object& operator=(const Object&& other) = delete;

		//Custom constructors
		Object(
			const float x,
			const float y,
			const float z,
			const float r,
			const float g,
			const float b);

		//Default constructors/destructor
		Object();
		~Object();

		//Member methods
		void Draw(GLuint shader) const;
		void SetVertices(std::vector<glm::vec2> vertices);
		glm::vec3& GetPosition() const;

		//PIMPL idiom
	protected:
		struct ObjectImpl;
		std::unique_ptr<ObjectImpl> _object_impl;
	};
}

#endif