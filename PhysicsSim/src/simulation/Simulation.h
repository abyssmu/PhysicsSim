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
		ThermodynamicParticleSimulator(const ThermodynamicParticleSimulator& other) = delete;
		ThermodynamicParticleSimulator& operator=(const ThermodynamicParticleSimulator& other) = delete;
		ThermodynamicParticleSimulator(const ThermodynamicParticleSimulator&& other) = delete;
		ThermodynamicParticleSimulator& operator=(const ThermodynamicParticleSimulator&& other) = delete;

		//Custom constructors
		ThermodynamicParticleSimulator(const int num_particles, const float radius);

		//Default constructors/destructor
		ThermodynamicParticleSimulator();
		~ThermodynamicParticleSimulator();

		//Member methods
		std::vector<std::shared_ptr<Object::Object>>& GetParticleCircles();

		//PIMPL idiom
	private:
		struct ThermodynamicParticleSimulatorImpl;
		std::unique_ptr<ThermodynamicParticleSimulatorImpl> _impl;
	};
}

#endif