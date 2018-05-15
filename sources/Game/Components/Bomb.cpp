#include "Game/Components/Bomb.hpp"
#include "Core/GameObject.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Component/ParticleBase.hpp"
#include "Core/Component/ParticleExplode.hpp"
#include "Core/Physics/Physics.hpp"
#include "Game/Assets.hpp"
#include "Game/Components/Breakable.hpp"
#include "Game/Components/Map.hpp"
#include "Core/Audio/AudioSource.hpp"
#include "Core/Audio/AudioClip.hpp"

namespace Game
{
	namespace Component
	{
		std::vector<Bomb*> Bomb::bombs;
		BeerEngine::Graphics::Texture *Bomb::explosionTexture = nullptr;

		Bomb::Bomb(BeerEngine::GameObject *gameObject) :
			Component(gameObject)
		{
			timer = 0.0f;
			power = 1.0f;
			bombs.push_back(this);
        }

		Bomb::~Bomb(void)
		{
			auto it = std::find(bombs.begin(), bombs.end(), this);
			if (it != bombs.end())
				bombs.erase(it);
		}

		void    Bomb::start(void)
		{
			render = _gameObject->GetComponent<BeerEngine::Component::MeshRenderer>();
			glm::vec2 mapPos = map->worldToMap(_gameObject->transform.position);
			map->mapUpdate(mapPos.x, mapPos.y, B);
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

		void	Bomb::explodeToward(glm::vec3 dir)
		{
			BeerEngine::Physics::RaycastHit				hit;
			float lifeTime = 1.0f / 2.0f;
			float sizeDeflag = (power + 0.25f) * 2.0f;
			auto bombDeflag = _gameObject->AddComponent<BeerEngine::Component::ParticleBase>();

			bombDeflag->setTexture(explosionTexture);
			bombDeflag->setColor(glm::vec4(1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
			bombDeflag->setAnimate(true, 64, 8, 8);
			bombDeflag->setLifeTime(lifeTime);
			if (BeerEngine::Physics::Physics::Raycast(_gameObject->transform.position, dir, hit, 1))
			{
				auto destroyable = hit.collider->_gameObject->GetComponent<Game::Component::Breakable>();
				if (destroyable)
					_gameObject->destroy(hit.collider->_gameObject);
				int distance = glm::distance(hit.transform->position, _gameObject->transform.position);
				sizeDeflag = (distance + 0.25f) * 2.0f;
			}
			bombDeflag->setSize(2.0f, 1.0f);
			bombDeflag->setSpawnTime(1.0f / 120.0f);
			dir = glm::normalize(dir) * sizeDeflag;
			bombDeflag->setVelocity(dir);
		}

		void	Bomb::explode(void)
		{
			if (render != nullptr)
			{
				auto *playerParticule = _gameObject->AddComponent<BeerEngine::Component::ParticleExplode>();
				playerParticule->setTexture(explosionTexture);
				playerParticule->setAnimate(true, 64, 8, 8);
				playerParticule->setLifeTime(0.5f);
				playerParticule->setSize(1.0f, 2.0f);
				playerParticule->setSpawnTime(1.0f / 120.0f);

				explodeToward(glm::vec3(power, 0.0f, 0.0f));
				explodeToward(glm::vec3(-power, 0.0f, 0.0f));
				explodeToward(glm::vec3(0.0f, 0.0f, power));
				explodeToward(glm::vec3(0.0f, 0.0f, -power));

				// BeerEngine::Audio::AudioClip   		clip("assets/sounds/Bomb+1.wav");
				// BeerEngine::Audio::AudioSource      srcAudio(clip.getBuffer());
				// srcAudio.setPosition(_gameObject->transform.position.x, _gameObject->transform.position.y, _gameObject->transform.position.z);
				// srcAudio.play();

				glm::vec2 mapPos = map->worldToMap(_gameObject->transform.position);
				map->mapUpdate(mapPos.x, mapPos.y, 0);

				_gameObject->destroy(_gameObject->GetComponent<BeerEngine::Component::ACollider>());
				_gameObject->destroy(render);
				onExplode.emit();
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
