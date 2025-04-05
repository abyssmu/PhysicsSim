/**
* @file NewClass.cpp
* @brief
* Function definitions for the NewClass. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "NewClass.h"

/// @brief NewNamespace namespace
namespace NewNamespace
{
	/// @brief NewClass PIMPL implementation structure.
	struct NewClass::NewClassImpl
	{
		//Deleted constructors

		/// @brief Deleted default constructor.
		NewClassImpl() = delete;
		/// @brief Deleted copy constructor.
		NewClassImpl(const NewClassImpl& other) = delete;
		/// @brief Deleted copy assignment operator.
		NewClassImpl& operator=(const NewClassImpl& other) = delete;
		/// @brief Deleted move constructor.
		NewClassImpl(const NewClassImpl&& other) = delete;
		/// @brief Deleted move assignment operator.
		NewClassImpl& operator=(const NewClassImpl&& other) = delete;

		//Custom constructors

		//Default constructors/destructor

		/// @brief Default destructor.
		~NewClassImpl() = default;

		//Member methods

		//Member variables
	};

	/**
	* @details
	* Default constructor for the NewClass class.
	*/
	NewClass::NewClass() = default;

	/**
	* @details
	* Default destructor for the NewClass class.
	*/
	NewClass::~NewClass() = default;
}