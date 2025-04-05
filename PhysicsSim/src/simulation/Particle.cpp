/**
* @file Particle.cpp
* @brief
* Function definitions for the Particle class. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "Particle.hpp"

#include "objects/Circle.hpp"

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
			*/
			ParticleImpl(
				const float radius,
				const float x,
				const float y,
				const float z,
				const float red,
				const float green,
				const float blue);

			//Default constructors/destructor

			/// @brief Default copy constructor.
			ParticleImpl(const ParticleImpl& other) = default;

			/// @brief Default destructor.
			~ParticleImpl() = default;

			//Member methods

			//Member variables

			/// @brief Circle object representing the particle.
			std::shared_ptr<Object::Object> circle;
		};

		/**
		* @details
		* Custom constructor for the ParticleImpl class. Passes the radius, position,
		* and color values to the Circle constructor.
		*/
		Particle::ParticleImpl::ParticleImpl(
			const float radius,
			const float x,
			const float y,
			const float z,
			const float red,
			const float green,
			const float blue) :
			circle(std::make_shared<Object::Circle>(radius, x, y, z, red, green, blue))
		{
		}

		/**
		* @details
		* Custom constructor for the Particle class. Passes the radius, position, and
		* color values to the ParticleImpl constructor.
		*/
		Particle::Particle(
			const float radius,
			const float x,
			const float y,
			const float z,
			const float red,
			const float green,
			const float blue) :
			_impl(std::make_unique<ParticleImpl>(radius, x, y, z, red, green, blue))
		{
		}

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
		* Get the circle object representing the particle.
		*/
		std::shared_ptr<Object::Object> Particle::GetCircle()
		{
			return _impl->circle;
		}
	}
}