/**
* @file Simulation.cpp
* @brief
* Function definitions for the simulation. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "Simulation.hpp"

#include "objects/Circle.hpp"
#include "objects/Object.hpp"
#include "Particle.hpp"

#include <random>

/// @brief Simulation namespace
namespace Simulation
{
	/// @brief ThermodynamicParticleSimulator PIMPL implementation structure
	struct ThermodynamicParticleSimulator::ThermodynamicParticleSimulatorImpl
	{
		//Deleted constructors

		/// @brief Deleted default constructor
		ThermodynamicParticleSimulatorImpl() = delete;
		/// @brief Deleted copy constructor
		ThermodynamicParticleSimulatorImpl(const ThermodynamicParticleSimulatorImpl& other) = delete;
		/// @brief Deleted copy assignment operator
		ThermodynamicParticleSimulatorImpl& operator=(const ThermodynamicParticleSimulatorImpl& other) = delete;
		/// @brief Deleted move constructor
		ThermodynamicParticleSimulatorImpl(const ThermodynamicParticleSimulatorImpl&& other) = delete;
		/// @brief Deleted move assignment operator
		ThermodynamicParticleSimulatorImpl& operator=(const ThermodynamicParticleSimulatorImpl&& other) = delete;

		//Custom constructors

		/**
		* @brief Custom constructor for the ThermodynamicParticleSimulatorImpl class.
		* @param num_particles The number of particles to simulate.
		* @param box_width_perc The width of the simulation box as a percentage of the window.
		* @param box_height_perc The height of the simulation box as a percentage of the window.
		* @param energy_value The energy value for the simulation.
		* @param temperature The temperature for the simulation.
		* @param chem_potential The chemical potential for the simulation.
		* @param radius The radius of the particles in the simulation.
		*/
		ThermodynamicParticleSimulatorImpl(
			const int num_particles,
			const int box_width_perc,
			const int box_height_perc,
			const float energy_value,
			const float temperature,
			const float chem_potential,
			const float radius);

		//Default constructors/destructor

		/// @brief Default destructor
		~ThermodynamicParticleSimulatorImpl() = default;

		//Member methods

		/**
		* @brief Setup the simulation with the given parameters.
		* @param num_particles The number of particles to simulate.
		* @param box_width_perc The width of the simulation box as a percentage of the window.
		* @param box_height_perc The height of the simulation box as a percentage of the window.
		* @param energy_value The energy value for the simulation.
		* @param temperature The temperature for the simulation.
		* @param chem_potential The chemical potential for the simulation.
		* @param radius The radius of the particles in the simulation.
		*/
		void SetupSimulation(
			const int num_particles,
			const int box_width_perc,
			const int box_height_perc,
			const float energy_value,
			const float temperature,
			const float chem_potential,
			const float radius);

		//Member variables

		/// @brief Vector of particles in the simulation
		std::vector<std::shared_ptr<SimulationItems::Particle>> particles;
		/// @brief Vector of circles representing the particles in the simulation
		std::vector<std::shared_ptr<Object::Object>> circles;
	};

	/**
	* @details
	* Custom constructor for the ThermodynamicParticleSimulatorImpl class. Passes
	* the parameters to the SetupSimulation method.
	*/
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

	/**
	* @details
	* Setup the simulation with the given parameters. This method generates a
	* number of particles and assigns them to random positions within the box
	* dimensions.
	*/
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

	/**
	* @details
	* Default constructor for the ThermodynamicParticleSimulatorImpl class.
	*/
	ThermodynamicParticleSimulator::ThermodynamicParticleSimulator() = default;
	
	/**
	* @details
	* Default destructor for the ThermodynamicParticleSimulator class.
	*/
	ThermodynamicParticleSimulator::~ThermodynamicParticleSimulator() = default;

	/**
	* @details
	* Custom constructor for the ThermodynamicParticleSimulator class. Passes the
	* parameters to the ThermodynamicParticleSimulatorImpl constructor.
	*/
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

	/**
	* @details
	* Clear the particles in the simulation. Clears both the particle and circle
	* vectors in the PIMPL implementation.
	*/
	void ThermodynamicParticleSimulator::ClearParticles()
	{
		_thermodynamic_impl->particles.clear();
		_thermodynamic_impl->circles.clear();
	}

	/**
	* @details
	* Get the particle circles in the simulation. Returns a reference to the
	* vector of circles in the PIMPL implementation.
	*/
	std::vector<std::shared_ptr<Object::Object>>& ThermodynamicParticleSimulator::GetParticleCircles()
	{
		return _thermodynamic_impl->circles;
	}

	/**
	* @details
	* Update the thermodynamics simulation. Passes the parameters to the
	* SetupSimulation method in the PIMPL implementation.
	*/
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