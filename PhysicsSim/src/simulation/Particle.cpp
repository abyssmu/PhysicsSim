/**
* @file Particle.cpp
* @brief
* Function definitions for the Particle class. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "Particle.hpp"

#include "graphics/objects/Circle.hpp"

/// @brief Simulation namespace
namespace Simulation
{
	/// @brief SimulationItems namespace
	namespace SimulationItems
	{

		/// @brief Particle PIMPL implementation structure.
		struct Particle::ParticleImpl
		{
			//Deleted constructors

			/// @brief Deleted default constructor.
			ParticleImpl() = delete;
			/// @brief Deleted copy assignment operator.
			ParticleImpl& operator=(const ParticleImpl& other) = delete;
			/// @brief Deleted move constructor.
			ParticleImpl(const ParticleImpl&& other) = delete;
			/// @brief Deleted move assignment operator.
			ParticleImpl& operator=(const ParticleImpl&& other) = delete;

			//Custom constructors

			/**
			* @brief Custom constructor for the ParticleImpl class.
			* @param radius The radius of the particle.
			* @param x The x-coordinate of the particle.
			* @param y The y-coordinate of the particle.
			* @param z The z-coordinate of the particle.
			* @param red The red color value of the particle.
			* @param green The green color value of the particle.
			* @param blue The blue color value of the particle.
			* @param x_scale The x scale value of the particle.
			* @param y_scale The y scale value of the particle.
			* @param z_scale The z scale value of the particle.
			*/
			ParticleImpl(
				const float x,
				const float y,
				const float z,
				const float red,
				const float green,
				const float blue,
				const float x_scale,
				const float y_scale,
				const float z_scale);

			//Default constructors/destructor

			/// @brief Default copy constructor.
			ParticleImpl(const ParticleImpl& other) = default;

			/// @brief Default destructor.
			~ParticleImpl() = default;

			//Member methods

			//Member variables

			/// @brief Position vector of the particle.
			std::vector<float> position;
			/// @brief Color vector of the particle.
			std::vector<float> color;
			/// @brief Scale vector of the particle.
			std::vector<float> scale;
		};

		/**
		* @details
		* Custom constructor for the ParticleImpl class. Initializes position,
		* color, and scale via lists with the corresponding parameters.
		*/
		Particle::ParticleImpl::ParticleImpl(
			const float x,
			const float y,
			const float z,
			const float red,
			const float green,
			const float blue,
			const float x_scale,
			const float y_scale,
			const float z_scale) :
			position({ x, y, z }),
			color({ red, green, blue }),
			scale({ x_scale, y_scale, z_scale })
		{}

		/**
		* @details
		* Custom constructor for the Particle class. Passes the position, color
		* and scale values to the ParticleImpl constructor.
		*/
		Particle::Particle(
			const float x,
			const float y,
			const float z,
			const float red,
			const float green,
			const float blue,
			const float x_scale,
			const float y_scale,
			const float z_scale) :
			_impl(std::make_unique<ParticleImpl>(
				x, y, z,
				red, green, blue,
				x_scale, y_scale, z_scale))
		{}

		/**
		* @details
		* Default constructor for the Particle class.
		*/
		Particle::Particle() = default;

		/**
		* @details
		* Default destructor for the Particle class.
		*/
		Particle::~Particle() = default;

		/**
		* @details
		* Get the position vector of the particle. The order of the vector is
		* x, y, z.
		*/
		std::vector<float> Particle::GetPosition() const
		{
			return _impl->position;
		}

		/**
		* @details
		* Get the color vector of the particle. The order of the vector is r, g, b.
		*/
		std::vector<float> Particle::GetColor() const
		{
			return _impl->color;
		}

		/**
		* @details
		* Get the scale vector of the particle. The order of the vector is x, y, z.
		*/
		std::vector<float> Particle::GetScale() const
		{
			return _impl->scale;
		}
	}
}