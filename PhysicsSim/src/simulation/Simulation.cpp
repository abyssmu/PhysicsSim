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
		ThermodynamicParticleSimulatorImpl(
			const int num_particles,
			const int box_width_perc,
			const int box_height_perc,
			const float energy_value,
			const float temperature,
			const float chem_potential,
			const float radius);

		//Default constructors/destructor
		~ThermodynamicParticleSimulatorImpl() = default;

		//Member methods
		void SetupSimulation(
			const int num_particles,
			const int box_width_perc,
			const int box_height_perc,
			const float energy_value,
			const float temperature,
			const float chem_potential,
			const float radius);

		//Member variables
		std::vector<std::shared_ptr<SimulationItems::Particle>> particles;
		std::vector<std::shared_ptr<Object::Object>> circles;
	};

	ThermodynamicParticleSimulator::ThermodynamicParticleSimulatorImpl::ThermodynamicParticleSimulatorImpl(
		const int num_particles,
		const int box_width_perc,
		const int box_height_perc,
		const float energy_value,
		const float temperature,
		const float chem_potential,
		const float radius)
	{
		SetupSimulation(
			num_particles,
			box_width_perc,
			box_height_perc,
			radius,
			temperature,
			chem_potential,
			radius);
	}

	void ThermodynamicParticleSimulator::ThermodynamicParticleSimulatorImpl::SetupSimulation(
		const int num_particles,
		const int box_width_perc,
		const int box_height_perc,
		const float energy_value,
		const float temperature,
		const float chem_potential,
		const float radius)
	{
		const float width = 1.50f;
		const float width_perc = float(box_width_perc) / 100.0f;
		const float height = 0.90f;
		const float height_perc = float(box_height_perc) / 100.0f;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> xdis(
			-width * width_perc,
			width * width_perc);
		std::uniform_real_distribution<float> ydis(
			-height * height_perc,
			height * height_perc);
		for (int i = 0; i < num_particles; i++)
		{
			float x = xdis(gen);
			float y = ydis(gen);
			float z = 0.0f;
			std::shared_ptr<SimulationItems::Particle> p =
				std::make_shared<SimulationItems::Particle>(
					radius,
					x,
					y,
					z,
					1.0f,
					0.0f,
					0.0f);
			particles.push_back(p);
			circles.push_back(particles[i]->GetCircle());
		}
	}

	ThermodynamicParticleSimulator::ThermodynamicParticleSimulator() = default;
	ThermodynamicParticleSimulator::~ThermodynamicParticleSimulator() = default;

	ThermodynamicParticleSimulator::ThermodynamicParticleSimulator(
		const int num_particles,
		const int box_width_perc,
		const int box_height_perc,
		const float energy_value,
		const float temperature,
		const float chem_potential,
		const float radius) :
		_thermodynamic_impl(std::make_unique<ThermodynamicParticleSimulator::ThermodynamicParticleSimulatorImpl>(
			num_particles,
			box_width_perc,
			box_height_perc,
			energy_value,
			temperature,
			chem_potential,
			radius))
	{}

	void ThermodynamicParticleSimulator::ClearParticles()
	{
		_thermodynamic_impl->particles.clear();
		_thermodynamic_impl->circles.clear();
	}

	std::vector<std::shared_ptr<Object::Object>>& ThermodynamicParticleSimulator::GetParticleCircles()
	{
		return _thermodynamic_impl->circles;
	}

	void ThermodynamicParticleSimulator::UpdateThermodynamicSimulation(
		const int num_particles,
		const int box_width_perc,
		const int box_height_perc,
		const float energy_value,
		const float temperature,
		const float chem_potential,
		const float radius)
	{
		_thermodynamic_impl->SetupSimulation(
			num_particles,
			box_width_perc,
			box_height_perc,
			energy_value,
			temperature,
			chem_potential,
			radius);
	}
}