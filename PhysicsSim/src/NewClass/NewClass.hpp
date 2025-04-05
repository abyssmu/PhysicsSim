/**
* @file NewClass.hpp
* @brief
* Blank template for creating a new class. Uses the PIMPL idiom to hide
* implementation details.
*/

#pragma once

#ifndef _NEWCLASS_
#define _NEWCLASS_

//External forward declarations

//Internal declarations

/// @brief NewNamespace namespace
namespace NewNamespace
{
	//External forward declarations

	//Internal declarations

	/// @brief NewClass class
	class NewClass
	{
	public:
		//Deleted constructors

		/// @brief Deleted copy constructor.
		NewClass(const NewClass& other) = delete;
		/// @brief Deleted copy assignment operator.
		NewClass& operator=(const NewClass& other) = delete;
		/// @brief Deleted move constructor.
		NewClass(const NewClass&& other) = delete;
		/// @brief Deleted move assignment operator.
		NewClass& operator=(const NewClass&& other) = delete;

		//Custom constructors

		//Default constructors/destructor

		/// @brief Constructor
		NewClass();
		/// @brief Destructor
		~NewClass();

		//Member methods

		//PIMPL idiom
	private:
		/// @brief Forward declaration of NewClassImpl struct.
		struct NewClassImpl;
		/// @brief Class member variable to hold the implementation details.
		std::unique_ptr<NewClassImpl> _impl;
	};
}

#endif