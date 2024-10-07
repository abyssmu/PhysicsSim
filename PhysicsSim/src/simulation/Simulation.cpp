#include "Simulation.h"

#include "objects/Circle.h"
#include "objects/Object.h"
#include "Particle.h"

#include <random>

namespace Simulation
{
	struct ThermodynamicParticleSimulator::ThermodynamicParticleSimulatorImpl
	{
		//Deleted constructors
		ThermodynamicParticleSimulatorImpl() = delete;
		ThermodynamicParticleSimulatorImpl(const ThermodynamicParticleSimulatorImpl& other) = delete;
		ThermodynamicParticleSimulatorImpl& operator=(const ThermodynamicParticleSimulatorImpl& other) = delete;
		ThermodynamicParticleSimulatorImpl(const ThermodynamicParticleSimulatorImpl&& other) = delete;
		ThermodynamicParticleSimulatorImpl& operator=(const ThermodynamicParticleSimulatorImpl&& other) = delete;

		//Custom constructors
		ThermodynamicParticleSimulatorImpl(const int num_particles, const float radius);

		//Default constructors/destructor
		~ThermodynamicParticleSimulatorImpl() = default;

		//Member methods

		//Member variables
		std::vector<std::shared_ptr<SimulationItems::Particle>> particles;
		std::vector<std::shared_ptr<Object::Object>> circles;
	};

	ThermodynamicParticleSimulator::ThermodynamicParticleSimulatorImpl::ThermodynamicParticleSimulatorImpl(
		const int num_particles,
		const float radius)
	{
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> xdis(-1.5f, 1.5f);
		std::uniform_real_distribution<float> ydis(-.95f, .95f);
		for (int i = 0; i < num_particles; i++)
		{
			float x = xdis(gen);
			float y = ydis(gen);
            float z = 0.0f;
			std::shared_ptr<SimulationItems::Particle> p = std::make_shared<SimulationItems::Particle>(radius, x, y, z, 1.0f, 0.0f, 0.0f);
			particles.push_back(p);
			circles.push_back(particles[i]->GetCircle());
		}
	}

	ThermodynamicParticleSimulator::ThermodynamicParticleSimulator() = default;
	ThermodynamicParticleSimulator::~ThermodynamicParticleSimulator() = default;

	ThermodynamicParticleSimulator::ThermodynamicParticleSimulator(const int num_particles, const float radius) :
		_impl(std::make_unique<ThermodynamicParticleSimulator::ThermodynamicParticleSimulatorImpl>(num_particles, radius))
	{}

	std::vector<std::shared_ptr<Object::Object>>& ThermodynamicParticleSimulator::GetParticleCircles()
	{
		return _impl->circles;
	}
}