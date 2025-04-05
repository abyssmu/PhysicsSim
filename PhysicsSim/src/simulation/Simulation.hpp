/**
* @file Application.hpp
* @brief
* Function declarations for the simulation. Uses the PIMPL idiom to hide
* implementation details.
*/

#pragma once

#ifndef _SIMULATION_
#define _SIMULATION_

#include <memory>
#include <vector>

//External forward declarations

/// @brief Forward declaration of Object namespace
namespace Object
{
	/// @brief Forward declaration of Object class in Object namespace
	class Object;
}

//Internal declarations

/// @brief Simulation namespace
namespace Simulation
{
	//External forward declarations

	//Internal declarations

	/// @brief ThermodynamicParticleSimulator class
	class ThermodynamicParticleSimulator
	{
	public:
		//Deleted constructors

		/// @brief Deleted copy constructor
		ThermodynamicParticleSimulator(
			const ThermodynamicParticleSimulator& other) = delete;
		/// @brief Deleted copy assignment operator
		ThermodynamicParticleSimulator& operator=(
			const ThermodynamicParticleSimulator& other) = delete;
		/// @brief Deleted move constructor
		ThermodynamicParticleSimulator(
			const ThermodynamicParticleSimulator&& other) = delete;
		/// @brief Deleted move assignment operator
		ThermodynamicParticleSimulator& operator=(
			const ThermodynamicParticleSimulator&& other) = delete;

		//Custom constructors

		/**
		* @brief Custom constructor for the ThermodynamicParticleSimulator class.
		* @param num_particles The number of particles to simulate.
		* @param box_width_perc The width of the simulation box as a percentage of the window.
		* @param box_height_perc The height of the simulation box as a percentage of the window.
		* @param energy_value The energy value for the simulation.
		* @param temperature The temperature for the simulation.
		* @param chem_potential The chemical potential for the simulation.
		* @param radius The radius of the particles in the simulation.
		*/
		ThermodynamicParticleSimulator(
			const int num_particles,
			const int box_width_perc,
			const int box_height_perc,
			const float energy_value,
			const float temperature,
			const float chem_potential,
			const float radius);

		//Default constructors/destructor

		/// @brief Default constructor for the ThermodynamicParticleSimulator class.
		ThermodynamicParticleSimulator();

		/// @brief Default destructor for the ThermodynamicParticleSimulator class.
		~ThermodynamicParticleSimulator();

		//Member methods

		/// @brief Clear the particles in the simulation.
		void ClearParticles();

		/**
		* @brief Get the particle circles in the simulation.
		* @return A vector of shared pointers to the particle circles.
		*/
		std::vector<std::shared_ptr<Object::Object>>& GetParticleCircles();

		/**
		* @brief Update the thermodynamic simulation.
		* @param num_particles The number of particles to simulate.
		* @param box_width_perc The width of the simulation box as a percentage of the window.
		* @param box_height_perc The height of the simulation box as a percentage of the window.
		* @param energy_value The energy value for the simulation.
		* @param temperature The temperature for the simulation.
		* @param chem_potential The chemical potential for the simulation.
		* @param radius The radius of the particles in the simulation.
		*/
		void UpdateThermodynamicSimulation(
			const int num_particles,
			const int box_width_perc,
			const int box_height_perc,
			const float energy_value,
			const float temperature,
			const float chem_potential,
			const float radius);

		//PIMPL idiom
	private:
		/// @brief Forward declaration of the ThermodynamicParticleSimulatorImpl class.
		struct ThermodynamicParticleSimulatorImpl;
		/// @brief Class member variable to hold the implementation details.
		std::unique_ptr<ThermodynamicParticleSimulatorImpl> _thermodynamic_impl;
	};
}

#endif