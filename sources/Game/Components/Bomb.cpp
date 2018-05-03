#include "Game/Components/Bomb.hpp"
#include "Core/GameObject.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Component/ParticleBase.hpp"
#include "Core/Component/ParticleExplode.hpp"
#include "Game/Assets.hpp"

namespace Game
{
	namespace Component
	{
		Bomb::Bomb(BeerEngine::GameObject *gameObject) :
			Component(gameObject)
		{
			timer = 0.0f;
			power = 1.0f;
        }

		void    Bomb::start(void)
		{
			render = _gameObject->GetComponent<BeerEngine::Component::MeshRenderer>();
		}

		void    Bomb::fixedUpdate(void)
		{
			timer += 1.0f / 60.0f;

			if (timer >= 5.0f)
			{
				if (timer >= 6.0f)
					_gameObject->destroy(_gameObject);
				else
					explode();
			}
			else
			{
				if (render != nullptr)
				{
					glm::vec4 color(1.0f);
					float t = timer - glm::floor(timer);
					if ((int)timer % 2 == 0)
					{
						color = glm::lerp(glm::vec4(1.0f), glm::vec4(1.0, 0.0, 0.0, 1.0), t);
						_gameObject->transform.scale = glm::lerp(glm::vec3(0.5f), glm::vec3(0.7f), t);
					}
					else
					{
						color = glm::lerp(glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec4(1.0f), t);
						_gameObject->transform.scale = glm::lerp(glm::vec3(0.7f), glm::vec3(0.5f), t);
					}
					render->getMaterial()->setColor(color);
				}
			}
		}

		void    Bomb::onColliderExit(BeerEngine::Component::ACollider *other)
		{
			BeerEngine::Component::ACollider *collider = _gameObject->GetComponent<BeerEngine::Component::ACollider>();
			if (!collider)
				return;
			auto it = std::find(collider->_exceptions.begin(), collider->_exceptions.end(), other);
			if (it != collider->_exceptions.end())
				collider->_exceptions.erase(it);
		}

		void	Bomb::explode(void)
		{
			if (render != nullptr)
			{
				auto *playerParticule = _gameObject->AddComponent<BeerEngine::Component::ParticleExplode>();
				playerParticule->setTexture(Assets::GetTexture("assets/textures/ParticleAtlas.png"));
				playerParticule->setAnimate(true, 64, 8, 8);
				playerParticule->setLifeTime(0.5f);
				playerParticule->setSize(1.0f, 2.0f);
				playerParticule->setSpawnTime(1.0f / 120.0f);

				float lifeTime = 1.0f / 2.0f;
				float sizeDeflag = (power + 0.25f) * 2.0f;

				auto playerDeflag0 = _gameObject->AddComponent<BeerEngine::Component::ParticleBase>();
				playerDeflag0->setTexture(Assets::GetTexture("assets/textures/ParticleAtlas.png"));
				playerDeflag0->setColor(glm::vec4(1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
				playerDeflag0->setAnimate(true, 64, 8, 8);
				playerDeflag0->setLifeTime(lifeTime);
				playerDeflag0->setSize(2.0f, 1.0f);
				playerDeflag0->setSpawnTime(1.0f / 120.0f);
				playerDeflag0->setVelocity(glm::vec3(sizeDeflag, 0.0f, 0.0f));

				auto playerDeflag1 = _gameObject->AddComponent<BeerEngine::Component::ParticleBase>();
				playerDeflag1->setTexture(Assets::GetTexture("assets/textures/ParticleAtlas.png"));
				playerDeflag1->setColor(glm::vec4(1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
				playerDeflag1->setAnimate(true, 64, 8, 8);
				playerDeflag1->setLifeTime(lifeTime);
				playerDeflag1->setSize(2.0f, 1.0f);
				playerDeflag1->setSpawnTime(1.0f / 120.0f);
				playerDeflag1->setVelocity(glm::vec3(-sizeDeflag, 0.0f, 0.0f));

				auto playerDeflag2 = _gameObject->AddComponent<BeerEngine::Component::ParticleBase>();
				playerDeflag2->setTexture(Assets::GetTexture("assets/textures/ParticleAtlas.png"));
				playerDeflag2->setColor(glm::vec4(1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
				playerDeflag2->setAnimate(true, 64, 8, 8);
				playerDeflag2->setLifeTime(lifeTime);
				playerDeflag2->setSize(2.0f, 1.0f);
				playerDeflag2->setSpawnTime(1.0f / 120.0f);
				playerDeflag2->setVelocity(glm::vec3(0.0f, 0.0f, sizeDeflag));

				auto playerDeflag3 = _gameObject->AddComponent<BeerEngine::Component::ParticleBase>();
				playerDeflag3->setTexture(Assets::GetTexture("assets/textures/ParticleAtlas.png"));
				playerDeflag3->setColor(glm::vec4(1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
				playerDeflag3->setAnimate(true, 64, 8, 8);
				playerDeflag3->setLifeTime(lifeTime);
				playerDeflag3->setSize(2.0f, 1.0f);
				playerDeflag3->setSpawnTime(1.0f / 120.0f);
				playerDeflag3->setVelocity(glm::vec3(0.0f, 0.0f, -sizeDeflag));

				_gameObject->destroy(render);
				render = nullptr;
				timer = 5.0f;
			}
		}

		void    Bomb::update(void)
		{}

		void	Bomb::setPower(float pow)
		{
			power = pow;
		}
	}
}