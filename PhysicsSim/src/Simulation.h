#pragma once

#ifndef _SIMULATION_
#define _SIMULATION_

#include <memory>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;

namespace Simulation
{
	class Simulator
	{
	public:
		Simulator(const Simulator& other) = delete;
		Simulator() = delete;
		~Simulator();
		Simulator(const string& name);

		string GetName();

	private:
		string name;
	};

	class Simulation
	{
		Simulation();
		~Simulation();
		Simulation(const Simulation& other);

		void CreateSimulator(const string& name);
		vector<string> GetSimulatorNames();

	private:
		vector<unique_ptr<Simulator>> sims;
	};
}

#endif