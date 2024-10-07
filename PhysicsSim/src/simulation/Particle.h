#pragma once

#ifndef _PARTICLE_
#define _PARTICLE_

#include <memory>

//External forward declarations
namespace Object
{
	class Object;
}

//Internal declarations
namespace SimulationItems
{
	//External forward declarations

	//Internal declarations
	class Particle
	{
	public:
		//Deleted constructors
		Particle(const Particle& other) = delete;
		Particle& operator=(const Particle& other) = delete;
		Particle(const Particle&& other) = delete;
		Particle& operator=(const Particle&& other) = delete;

		//Custom constructors
		Particle(
			const float radius,
			const float x,
			const float y,
			const float z,
			const float red,
			const float green,
			const float blue);

		//Default constructors/destructor
		Particle();
		~Particle();

		//Member methods
		std::shared_ptr<Object::Object> GetCircle();

		//PIMPL idiom
	private:
		struct ParticleImpl;
		std::unique_ptr<ParticleImpl> _impl;
	};
}

#endif