#pragma once

#ifndef _SIMULATION_
#define _SIMULATION_

#include <memory>
#include <vector>

//External forward declarations
namespace Object
{
	class Object;
}

//Internal declarations
namespace Simulation
{
	//External forward declarations

	//Internal declarations
	class ThermodynamicParticleSimulator
	{
	public:
		//Deleted constructors
		ThermodynamicParticleSimulator(
			const ThermodynamicParticleSimulator& other) = delete;
		ThermodynamicParticleSimulator& operator=(
			const ThermodynamicParticleSimulator& other) = delete;
		ThermodynamicParticleSimulator(
			const ThermodynamicParticleSimulator&& other) = delete;
		ThermodynamicParticleSimulator& operator=(
			const ThermodynamicParticleSimulator&& other) = delete;

		//Custom constructors
		ThermodynamicParticleSimulator(
			const int num_particles,
			const int box_width_perc,
			const int box_height_perc,
			const float energy_value,
			const float temperature,
			const float chem_potential,
			const float radius);

		//Default constructors/destructor
		ThermodynamicParticleSimulator();
		~ThermodynamicParticleSimulator();

		//Member methods
		void ClearParticles();
		std::vector<std::shared_ptr<Object::Object>>& GetParticleCircles();
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
		struct ThermodynamicParticleSimulatorImpl;
		std::unique_ptr<ThermodynamicParticleSimulatorImpl> _thermodynamic_impl;
	};
}

#endif