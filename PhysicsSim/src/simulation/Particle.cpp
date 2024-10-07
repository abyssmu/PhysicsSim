#include "Particle.h"

#include "objects/Circle.h"

namespace SimulationItems
{
	struct Particle::ParticleImpl
	{
		//Deleted constructors
		ParticleImpl() = delete;
		ParticleImpl& operator=(const ParticleImpl& other) = delete;
		ParticleImpl(const ParticleImpl&& other) = delete;
		ParticleImpl& operator=(const ParticleImpl&& other) = delete;

		//Custom constructors
		ParticleImpl(
			const float radius,
			const float x,
			const float y,
			const float z,
			const float red,
			const float green,
			const float blue);

		//Default constructors/destructor
		ParticleImpl(const ParticleImpl& other) = default;
		~ParticleImpl() = default;

		//Member methods

		//Member variables
		std::shared_ptr<Object::Object> circle;
	};

	Particle::ParticleImpl::ParticleImpl(
		const float radius,
		const float x,
		const float y,
		const float z,
		const float red,
		const float green,
		const float blue) :
		circle(std::make_shared<Object::Circle>(radius, x, y, z, red, green, blue))
	{}

	Particle::Particle(
		const float radius,
		const float x,
		const float y,
		const float z,
		const float red,
		const float green,
		const float blue) :
		_impl(std::make_unique<ParticleImpl>(radius, x, y, z, red, green, blue))
	{}

	Particle::Particle() = default;
	Particle::~Particle() = default;

	std::shared_ptr<Object::Object> Particle::GetCircle()
	{
		return _impl->circle;
	}
}