/**
* @file ThermodynamicsRenderItems.hpp
* @brief
* Blank template for creating a new class. Uses the PIMPL idiom to hide
* implementation details.
*/

#pragma once

#ifndef _ThermodynamicsRenderItems_
#define _ThermodynamicsRenderItems_

#include "SimulationRenderItems.hpp"

#include <memory>
#include <vector>

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
		/// @brief Thermodynamics particle vertex shader file path
		static const std::string PARTICLE_VS_PATH =
			"src/graphics/shaders/ParticleVertexShader.vs";
		/// @brief Thermodynamics particle fragment shader file path
		static const std::string PARTICLE_FS_PATH =
			"src/graphics/shaders/ParticleFragmentShader.fs";

		/// @brief ThermodynamicsRenderItems class
		class ThermodynamicsRenderItems : public SimulationRenderItems
		{
		public:
			//Deleted constructors

			/// @brief Deleted copy constructor.
			ThermodynamicsRenderItems(const ThermodynamicsRenderItems& other) = delete;
			/// @brief Deleted copy assignment operator.
			ThermodynamicsRenderItems& operator=(const ThermodynamicsRenderItems& other) = delete;
			/// @brief Deleted move constructor.
			ThermodynamicsRenderItems(const ThermodynamicsRenderItems&& other) = delete;
			/// @brief Deleted move assignment operator.
			ThermodynamicsRenderItems& operator=(const ThermodynamicsRenderItems&& other) = delete;

			//Custom constructors

			/**
			* @brief Custom constructor for the ThermodynamicsRenderItems class.
			* @param particles Vector of particle data.
			* @param radius The radius of the particles.
			*/
			ThermodynamicsRenderItems(
				std::vector<float>& particles,
				const float radius);

			//Default constructors/destructor

			/// @brief Default constructor.
			ThermodynamicsRenderItems();
			/// @brief Default destructor.
			~ThermodynamicsRenderItems();

			//Member methods

			/// @brief Render method for the thermodynamic simulation items.
			void Render() override;

			//PIMPL idiom
		private:
			/// @brief Forward declaration of ThermodynamicsRenderItemsImpl struct.
			struct ThermodynamicsRenderItemsImpl;
			/// @brief Class member variable to hold the implementation details.
			std::unique_ptr<ThermodynamicsRenderItemsImpl> _impl;
		};
	}
}

#endif