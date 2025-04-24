/**
* @file Simulation.cpp
* @brief
* Function definitions for the simulation. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "Simulation.hpp"
#include "Particle.hpp"

#include "graphics/Shader.hpp"
#include "graphics/objects/Object.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
		particles.clear();

		/*
		* Setup the particles using uniform distribution for the X and Y
		* coordinates. With the given width and height percentages as the limits.
		* 
		*/
		const float width_perc = float(box_width_perc) / 100.0f * 0.90f;
		const float height_perc = float(box_height_perc) / 100.0f * 0.90f;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> xdis(-width_perc, width_perc);
		std::uniform_real_distribution<float> ydis(-height_perc, height_perc);
		for (int i = 0; i < num_particles; i++)
		{
			float x = xdis(gen);
			float y = ydis(gen);
			float z = 0.0f;
			float red = 1.0f;
			float green = 0.0f;
			float blue = 0.0f;
			float x_scale = 1.0f;
			float y_scale = 1.0f;
			float z_scale = 1.0f;
			std::shared_ptr<SimulationItems::Particle> p =
				std::make_shared<SimulationItems::Particle>(
					x,
					y,
					z,
					red,
					green,
					blue,
					x_scale,
					y_scale,
					z_scale);
			particles.push_back(p);
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
	* Empty the vector of particles
	*/
	void ThermodynamicParticleSimulator::ClearParticles()
	{
	}

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
	* Generate and return the instance data for the particles.
	*/
	std::vector<float> ThermodynamicParticleSimulator::GetParticleInstanceData()
	{
		std::vector<float> out;

		for (const auto& particle : _thermodynamic_impl->particles)
		{
			auto p = particle->GetPosition();
			auto c = particle->GetColor();
			auto s = particle->GetScale();
			out.insert(out.end(), p.begin(), p.end());
			out.push_back(1.0f);
			out.insert(out.end(), c.begin(), c.end());
			out.push_back(1.0f);
			out.insert(out.end(), s.begin(), s.end());
			out.push_back(1.0f);
		}

		return out;
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