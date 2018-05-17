#include "Core/Component/ParticleExplode.hpp"
#include "Core/GameObject.hpp"
#include "Core/Time.hpp"
#include "Core/Camera.hpp"
#include "Core/Window.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Mathf.hpp"

namespace BeerEngine
{
	namespace Component
	{
		ParticleExplode::ParticleExplode(GameObject *gameObject) :
			ParticleBase(gameObject)
		{}

		void ParticleExplode::initParticle(Particle &particle)
		{
			velocity.x = Mathf::Range(-1.0f, 1.0f);
			velocity.y = Mathf::Range(-1.0f, 1.0f);
			velocity.z = Mathf::Range(-1.0f, 1.0f);
			velocity = glm::normalize(velocity);
			particle.life = lifeTime;
			particle.position = _gameObject->transform.getWorldPosition() + offset;
			particle.velocity = _gameObject->transform.getWorldRotate(velocity);
			particle.lifeAnimSpeed = ((float)rand() / RAND_MAX) + 0.9f;
		}

		nlohmann::json	ParticleExplode::serialize()
		{
			auto j = ParticleBase::serialize();
			j.merge_patch({
				{"componentClass", type},
			});
			return j;
		}

		void ParticleExplode::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			this->ParticleBase::deserialize(j, loader);
		}

		REGISTER_COMPONENT_CPP(ParticleExplode)
	}
}