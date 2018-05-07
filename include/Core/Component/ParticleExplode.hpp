#ifndef BE_CORE_COMPONENT_PARTICLEEXPLODE_HPP
#define BE_CORE_COMPONENT_PARTICLEEXPLODE_HPP 1

#include "ParticleBase.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class ParticleExplode : public ParticleBase
		{
		public:
			ParticleExplode(GameObject *gameObject);
			virtual void initParticle(Particle &particle);

			virtual nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif