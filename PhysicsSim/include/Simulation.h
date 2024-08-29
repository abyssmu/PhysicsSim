#pragma once

#ifndef _SIMULATION_
#define _SIMULATION_

#include <memory>
#include <string>

namespace Simulation
{
	class Simulator
	{
	public:
		//Deleted constructors
		Simulator(const Simulator& other) = delete;
		Simulator& operator=(const Simulator& other) = delete;
		Simulator(const Simulator&& other) = delete;
		Simulator& operator=(const Simulator&& other) = delete;

		//Custom constructors
		Simulator(const std::string& name);

		//Default constructors/destructor
		Simulator();
		~Simulator();

		//Member methods

		//PIMPL idiom
	private:
		struct SimulatorImpl;
		std::unique_ptr<SimulatorImpl> _impl;
	};
}

#endif