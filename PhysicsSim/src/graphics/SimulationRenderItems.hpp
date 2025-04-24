/**
* @file SimulationRenderStructs.hpp
* @brief
* Render data structure declarations for individual simulations.
*/

#pragma once

#ifndef _SIMULATIONRENDERSTRUCTS_
#define _SIMULATIONRENDERSTRUCTS_

#include <memory>
#include <string>

//External forward declarations

//Internal declarations

/// @brief Graphics namespace
namespace Graphics
{
	//External forward declarations

	//Internal declarations

	/// @brief SimulationRenderStructs namespace
	namespace SimulationRenderStructs
	{
		/// @brief SimulationRenderItems class.
		class SimulationRenderItems
		{
		public:
			//Deleted constructors

			/// @brief Deleted copy constructor.
			SimulationRenderItems(const SimulationRenderItems& other) = delete;
			/// @brief Deleted copy assignment operator.
			SimulationRenderItems& operator=(const SimulationRenderItems& other) = delete;
			/// @brief Deleted move constructor.
			SimulationRenderItems(SimulationRenderItems&& other) = delete;
			/// @brief Deleted move assignment operator.
			SimulationRenderItems& operator=(const SimulationRenderItems&& other) = delete;

			//Custom constructors

			/**
			* @brief Custom constructor for the SimulationRenderItems class.
			* @param vs_file The vertex shader file.
			* @param fs_file The fragment shader file.
			*/
			SimulationRenderItems(
				const std::string& vs_file,
				const std::string& fs_file);
			
			//Default constructors/destructor

			/// @brief Default constructor.
			SimulationRenderItems();
			/// @brief Virtual destructor.
			~SimulationRenderItems();

			//Member Methods

			/**
			* @brief Get the GLFW shader object.
			* @return The GLFW shader object.
			*/
			unsigned int& GetShader() const;

			/// @brief Virtual render method.
			virtual void Render() = 0;

			//PIMPL idiom
		private:
			/// @brief Forward declaration of SimulationRenderItemsImpl struct.
			struct SimulationRenderItemsImpl;
			/// @brief Class member variable to hold the implementation details.
			std::unique_ptr<SimulationRenderItemsImpl> _impl;
		};
	}
}

#endif