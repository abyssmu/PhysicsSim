#include "Simulation.h"

namespace Simulation
{
	Simulator::~Simulator() {}
	Simulator::Simulator(const string& name) : name(name) {}

	string Simulator::GetName() { return name; }



	Simulation::Simulation() {}
	Simulation::~Simulation() {}
	Simulation::Simulation(const Simulation& other) {}

	void Simulation::CreateSimulator(const std::string& name)
	{
		sims.push_back(make_unique<Simulator>(name));
	}

	vector<string> Simulation::GetSimulatorNames()
	{
		vector<string> names;
		for (size_t i = 0; i < sims.size(); ++i)
		{
			names.push_back(sims[i]->GetName());
		}

		return names;
	}
}