/**
* @file Shader.hpp
* @brief
* Function declarations to create and manage shaders. Uses the PIMPL idiom to hide
* implementation details.
*/

#pragma once

#ifndef _SHADER_
#define _SHADER_

#include <memory>
#include <string>

//External forward declarations

/// @brief Forward declaration of GLuint.
typedef unsigned int GLuint;

//Internal declarations

/// @brief Scene namespace
namespace Scene
{
	//External fordward declarations

	//Internal declarations

	/// @brief Shader class
	class Shader
	{
	public:
		//Deleted constructors

		/// @brief Deleted copy constructor.
		Shader(const Shader& other) = delete;
		/// @brief Deleted copy assignment operator.
		Shader& operator=(const Shader& other) = delete;
		/// @brief Deleted move constructor.
		Shader(Shader&& other) = delete;
		/// @brief Deleted move assignment operator.
		Shader& operator=(const Shader&& other) = delete;
		
		//Custom constructors
		
		/**
		* @brief Custom constructor for the Shader class.
		* @param vs_file The vertex shader file.
		* @param fs_file The fragment shader file.
		*/
		Shader(const std::string& vs_file, const std::string& fs_file);

		//Default constructors/destructor

		/// @brief Default constructor.
		Shader();
		/// @brief Default destructor.
		~Shader();

		//Member methods

		/**
		* @brief Get the OpenGL shader ID.
		* @return The OpenGL shader ID.
		*/
		GLuint& GetShader();

		//PIMPL idiom
	private:
		/// @brief Forward declaration of ShaderImpl.
		struct ShaderImpl;
		/// @brief Class member variable to hold the implementation details.
		std::unique_ptr<ShaderImpl> _impl;
	};
}

#endif