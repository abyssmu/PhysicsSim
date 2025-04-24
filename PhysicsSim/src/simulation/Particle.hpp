/**
* @file Particle.hpp
* @brief
* Function declarations for the Particle class. Uses the PIMPL idiom to hide
* implementation details.
*/

#pragma once

#ifndef _PARTICLE_
#define _PARTICLE_

#include <memory>
#include <vector>

//External forward declarations

/// @brief Forward declaration of the Object namespace
namespace Object
{
	/// @brief Forward declaration of the Object class
	class Object;
}

//Internal declarations

/// @brief Simulation namespace
namespace Simulation
{
	/// @brief SimulationItems namespace
	namespace SimulationItems
	{
		//External forward declarations

		//Internal declarations

		/// @brief Particle class
		class Particle
		{
		public:
			//Deleted constructors

			/// @brief Deleted copy constructor.
			Particle(const Particle& other) = delete;
			/// @brief Deleted copy assignment operator.
			Particle& operator=(const Particle& other) = delete;
			/// @brief Deleted move constructor.
			Particle(const Particle&& other) = delete;
			/// @brief Deleted move assignment operator.
			Particle& operator=(const Particle&& other) = delete;

			//Custom constructors

			/**
			* @brief Custom constructor for the Particle class.
			* @param radius The radius of the particle.
			* @param x The x-coordinate of the particle.
			* @param y The y-coordinate of the particle.
			* @param z The z-coordinate of the particle.
			* @param red The red color value of the particle.
			* @param green The green color value of the particle.
			* @param blue The blue color value of the particle.
			*/
			Particle(
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

			/// @brief Default constructor for the Particle class.
			Particle();
			/// @brief Default destructor for the Particle class.
			~Particle();

			//Member methods

			/**
			* @brief Get the position vector of the particle.
			* @return The position vector of the particle.
			*/
			std::vector<float> GetPosition() const;

			/**
			* @brief Get the color vector of the particle.
			* @return The color vector of the particle.
			*/
			std::vector<float> GetColor() const;

			/**
			* @brief Get the scale vector of the particle.
			* @return The scale vector of the particle.
			*/
			std::vector<float> GetScale() const;

			//PIMPL idiom
		private:
			/// @brief Forward declaration of the ParticleImpl class
			struct ParticleImpl;
			/// @brief Class member variable to hold the implementation details.
			std::unique_ptr<ParticleImpl> _impl;
		};
	}
}

#endif