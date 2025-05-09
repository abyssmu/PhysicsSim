/**
* @file Object.hpp
* @brief
* Function declarations for the Object class. Uses the PIMPL idiom to hide
* implementation details.
*/

#pragma once

#ifndef _OBJECT_
#define _OBJECT_

#include <glm/glm.hpp>

#include <memory>
#include <vector>

//External forward declarations

/// @brief Forward declaration of GLuint.
typedef unsigned int GLuint;

//Internal declarations

/// @brief Object namespace
namespace Object
{
	//External forward declarations

	//Internal declarations

	/// @brief Object class
	class Object
	{
	public:
		//Deleted constructors

		/// @brief Deleted copy constructor.
		Object(const Object& other) = delete;
		/// @brief Deleted copy assignment operator.
		Object& operator=(const Object& other) = delete;
		/// @brief Deleted move constructor.
		Object(const Object&& other) = delete;
		/// @brief Deleted move assignment operator.
		Object& operator=(const Object&& other) = delete;

		//Custom constructors

		/**
		* @brief Custom constructor for the Object class.
		* @param x The x-coordinate of the object.
		* @param y The y-coordinate of the object.
		* @param z The z-coordinate of the object.
		* @param r The red color value of the object.
		* @param g The green color value of the object.
		* @param b The blue color value of the object.
		*/
		Object(
			const float x,
			const float y,
			const float z,
			const float r,
			const float g,
			const float b);

		//Default constructors/destructor

		/// @brief Default constructor.
		Object();
		/// @brief Default destructor.
		~Object();

		//Member methods

		/**
		* @brief Draw the object with the given shader.
		* @param shader The shader to use for drawing.
		*/
		void Draw(GLuint shader) const;

		/**
		* @brief Set the vertices of the object.
		* @param vertices The vector of vertices to set.
		*/
		void SetVertices(std::vector<glm::vec2> vertices);

		/**
		* @brief Get the number of vertices in the object.
		* @return The number of vertices in the object.
		*/
		int GetNumVertices() const;

		/**
		* @brief Get the position of the object.
		* @return GLM vector of the object's position.
		*/
		glm::vec3& GetPosition() const;

		/**
		* @brief Get the color of the object.
		* @return GLM vector of the object's color.
		*/
		glm::vec3& GetColor() const;

		/**
		* @brief Get the vertex buffer array object.
		* @return Reference to the vertex buffer array object.
		*/
		GLuint& GetVBO() const;

		/**
		* @brief Get the vertex array object.
		* @return Reference to the vertex array object.
		*/
		GLuint& GetVAO() const;

		//PIMPL idiom
	protected:
		/// @brief Forward declaration of ObjectImpl.
		struct ObjectImpl;
		/// @brief Class member variable to hold the implementation details.
		std::unique_ptr<ObjectImpl> _object_impl;
	};
}

#endif