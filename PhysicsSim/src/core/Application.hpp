/**
* @file Application.hpp
* @brief
* Function declarations to initialize and manage the application. Defines the 
* WIN32_LEAN_AND MEAN directive. Uses the PIMPL idiom to hide implementation details.
*/

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _APPLICATION_
#define _APPLICATION_

#include <memory>
#include <string>

//External forward declarations

/// @brief Forward declaration of Object namespace.
namespace Object
{
	/// @brief Forward declaration of Object class in Object namespace.
	class Object;
}

//Internal declarations

/// @brief Application namespace
namespace App
{
	//External forward declarations

	/// @brief Forward declaration of ThermodynamicSimulationVariables struct.
	struct ThermodynamicSimulationVariables;

	//Internal declarations

	/// @brief Application class
	class Application
	{
	public:
		//Deleted constructors

		/// @brief Deleted copy constructor.
		Application(const Application& other) = delete;
		/// @brief Deleted copy assignment operator.
		Application& operator=(const Application& other) = delete;
		/// @brief Deleted move constructor.
		Application(const Application&& other) = delete;
		/// @brief Deleted move assignment operator.
		Application& operator=(const Application&& other) = delete;

		//Custom constructors

		//Default constructors/destructor

		/// @brief Constructor
		Application();
		/// @brief Default destructor
		~Application();

		//Member methods

		/**
		* @brief Initialize the application.
		* @param name The name of the application.
		* @param width The width of the application window.
		* @param height The height of the application window.
		* @return True if the application was initialized successfully, false otherwise.
		*/
		bool Init(const std::string& name, const int& width, const int& height);

		/**
		* @brief Run the application.
		* @param demo True if the application is running in demo mode, false otherwise.
		*/
		void Run(bool demo);

		//PIMPL idiom
	private:
		/// @brief Forward declaration of ApplicationImpl struct.
		struct ApplicationImpl;
		/// @brief Class member variable to hold the implementation details.
		std::unique_ptr<ApplicationImpl> _impl;
	};
}

#endif