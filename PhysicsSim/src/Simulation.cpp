#include "Simulation.h"

namespace Simulation
{
	struct Simulator::SimulatorImpl
	{
		//Deleted constructors
		SimulatorImpl() = delete;
		SimulatorImpl(const SimulatorImpl& other) = delete;
		SimulatorImpl& operator=(const SimulatorImpl& other) = delete;
		SimulatorImpl(const SimulatorImpl&& other) = delete;
		SimulatorImpl& operator=(const SimulatorImpl&& other) = delete;

		//Custom constructors
		SimulatorImpl(const std::string& name);

		//Default constructors/destructor
		~SimulatorImpl() = default;

		//Member methods

		//Member variables
		std::string name;
	};

	Simulator::SimulatorImpl::SimulatorImpl(const std::string& name) :
		name(name)
	{}

	Simulator::Simulator() {}
	Simulator::~Simulator() {}

	Simulator::Simulator(const std::string& name) :
		_impl(std::make_unique<SimulatorImpl>(name))
	{}
}