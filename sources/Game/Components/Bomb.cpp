#include "Game/Components/Bomb.hpp"
#include "Core/GameObject.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Component/ParticleBase.hpp"
#include "Core/Component/ParticleExplode.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Physics/Physics.hpp"
#include "Game/Assets.hpp"
#include "Game/Components/Breakable.hpp"
#include "Game/Components/Map.hpp"
#include "Game/Components/IA.hpp"
#include "Game/Components/AudioManager.hpp"
#include "Game/Components/GameManager.hpp"
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
			hitDir = new glm::vec3[4];
			for (int i = 0; i < 4; i++)
				hitDir[i] = glm::vec3(_gameObject->transform.position);
        }

		Bomb::Bomb(void)
		{}

		Bomb::Bomb(const Bomb &val)
		{
			*this = val;
		}

		Bomb &Bomb::operator=(const Bomb &val)
		{
			(void) val;
			if (this != &val)
			{ }
			return (*this);
		}

		Bomb::~Bomb(void)
		{
			auto it = std::find(bombs.begin(), bombs.end(), this);
			if (it != bombs.end())
				bombs.erase(it);
			delete hitDir;
		}

		void    Bomb::start(void)
		{
			render = _gameObject->GetComponent<BeerEngine::Component::MeshRenderer>();
			glm::vec2 mapPos = map->worldToMap(_gameObject->transform.position);
			map->mapUpdate(mapPos.x, mapPos.y, B);
			auto collider = _gameObject->GetComponent<BeerEngine::Component::CircleCollider>();
            auto characterCol = map->_player->_gameObject->GetComponent<BeerEngine::Component::ACollider>();
            if (characterCol && collider->checkCollision(characterCol, false))
                collider->_exceptions.push_back(characterCol);
            for (Game::Component::IA *ia : map->_IAs)
            {
                characterCol = ia->_gameObject->GetComponent<BeerEngine::Component::ACollider>();
                if (characterCol && collider->checkCollision(characterCol, false))
                    collider->_exceptions.push_back(characterCol);
            }
		}

		void    Bomb::fixedUpdate(void)
		{
			timer += 1.0f / 60.0f;

			if (timer >= 5.0f)
			{
				explodeUpdateMap();
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
						_gameObject->transform.scale = glm::lerp(glm::vec3(0.15f), glm::vec3(0.25f), t);
					}
					else
					{
						color = glm::lerp(glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec4(1.0f), t);
						_gameObject->transform.scale = glm::lerp(glm::vec3(0.25f), glm::vec3(0.15f), t);
					}
					render->getMaterial()->setColor(color);
				}
			}
		}

		void	Bomb::explodeTowardUpdateMap(int value)
		{
			static glm::vec3 dir[] = {
				glm::vec3(1, 0, 0),
				glm::vec3(-1, 0, 0),
				glm::vec3(0, 0, 1),
				glm::vec3(0, 0, -1)
			};
			for (int j = 0; j < 4; j++)
			{
				int d = static_cast<int>(glm::distance(hitDir[j], _gameObject->transform.position));
				for (int i = 1; i <= d; i++)
				{
					glm::vec3 np = (_gameObject->transform.position + (dir[j] * i));
					glm::vec2 mapPos = map->worldToMap(np);
					if (map->hasWall(glm::vec2(mapPos.x, mapPos.y)))
						break;
					map->mapUpdate(mapPos.x, mapPos.y, value);
				}
			}
		}

		void	Bomb::explodeUpdateMap(void)
		{
			glm::vec2 mapPos = map->worldToMap(_gameObject->transform.position);
			if (timer >= 6.0f)
			{
				map->mapUpdate(mapPos.x, mapPos.y, 0);
				explodeTowardUpdateMap(0);
			}
			else
			{
				map->mapUpdate(mapPos.x, mapPos.y, B);
				explodeTowardUpdateMap(B);
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

		void	Bomb::explodeToward(glm::vec3 dir, int hitIDStorage)
		{
			hitDir[hitIDStorage] = _gameObject->transform.position + dir;
			std::vector<BeerEngine::Physics::RaycastHit> hits = BeerEngine::Physics::Physics::RaycastAllOrdered(_gameObject->transform.position, dir);
			// float lifeTime = 1.0f / 2.0f;
			// float sizeDeflag = (power + 0.25f) * 2.0f;
			float sizeDeflag = glm::length(dir);
			// auto bombDeflag = _gameObject->AddComponent<BeerEngine::Component::ParticleBase>();
			std::size_t i = 0;

			// bombDeflag->setTexture(explosionTexture);
			// bombDeflag->setColor(glm::vec4(1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
			// bombDeflag->setAnimate(true, 64, 8, 8);
			// bombDeflag->setLifeTime(lifeTime);
			// bombDeflag->offset = glm::vec3(0, 0.5f, 0);
			if (hits.size() >= 1)
			{
				if (hits[0].collider->_gameObject == _gameObject)
					i = 1;
				if (i < hits.size())
				{
					int distance = glm::distance(hits[i].transform->position, _gameObject->transform.position);
					hitDir[hitIDStorage] = glm::floor(hits[i].transform->position);
					//power
					auto destroyable = hits[i].collider->_gameObject->GetComponent<Game::Component::Breakable>();
					auto bomb = hits[i].collider->_gameObject->GetComponent<Game::Component::Bomb>();
					if (destroyable)
						_gameObject->destroy(hits[i].collider->_gameObject);
					if (bomb)
						bomb->timer = 5.0f;
					sizeDeflag = distance;
					if (!destroyable && !bomb)
						sizeDeflag -= 1.0f;
					// sizeDeflag = (distance + 0.25f) * 2.0f;
					// if (sizeDeflag <= 0)
					// 	sizeDeflag = 0.0f;
					// else
					// 	sizeDeflag -= 1.0f;
				}
			}
			else
			{
				hitDir[hitIDStorage] = glm::floor(_gameObject->transform.position + glm::normalize(dir) * power);
			}



			int size = static_cast<int>(sizeDeflag);
			for (int i = 1; i <= size; i++)
			{
				auto *explodeParticule = _gameObject->AddComponent<BeerEngine::Component::ParticleExplode>();
				explodeParticule->setTexture(explosionTexture);
				explodeParticule->setAnimate(true, 64, 8, 8);
				explodeParticule->setLifeTime(0.5f);
				explodeParticule->setSize(1.0f, 2.0f);
				explodeParticule->setSpawnTime(1.0f / 120.0f);
				explodeParticule->offset = glm::vec3(0, 0.25f, 0.5f) + glm::normalize(dir) * i;
			}
			// bombDeflag->setSize(2.0f);
			// float timeToSpawnByPower = 90.0f + power * 30.0f;
			// bombDeflag->setSpawnTime(1.0f / timeToSpawnByPower);
			// dir = glm::normalize(dir) * sizeDeflag;
			// bombDeflag->setVelocity(dir);
		}

		void	Bomb::explode(void)
		{
			if (render != nullptr)
			{
				auto soundManager = _gameObject->AddComponent<Game::Component::AudioManager>();
				soundManager->setClip("assets/sounds/Bomb+1.wav");
				soundManager->setPosition(_gameObject->transform.position.x, _gameObject->transform.position.y, _gameObject->transform.position.z);

				auto *playerParticule = _gameObject->AddComponent<BeerEngine::Component::ParticleExplode>();
				playerParticule->setTexture(explosionTexture);
				playerParticule->setAnimate(true, 64, 8, 8);
				playerParticule->setLifeTime(0.5f);
				playerParticule->setSize(1.0f, 2.0f);
				playerParticule->setSpawnTime(1.0f / 120.0f);
				playerParticule->offset = glm::vec3(0, 0.5f, 0.5f);
				explodeToward(glm::vec3(power, 0.0f, 0.0f), 0);
				explodeToward(glm::vec3(-power, 0.0f, 0.0f), 1);
				explodeToward(glm::vec3(0.0f, 0.0f, power), 2);
				explodeToward(glm::vec3(0.0f, 0.0f, -power), 3);

				_gameObject->destroy(_gameObject->GetComponent<BeerEngine::Component::ACollider>());
				_gameObject->destroy(render);
				if (GameManager::GetInstance().storyMode == false)
					onExplode.emit();
				render = nullptr;
				timer = 5.0f;
			}
			else
			{
				for (int j = 0; j < 4; j++)
				{
					std::size_t i = 0;
					glm::vec3 dir = hitDir[j] - _gameObject->transform.position;
					std::vector<BeerEngine::Physics::RaycastHit> hits = BeerEngine::Physics::Physics::RaycastAllOrdered(_gameObject->transform.position, dir);
					if (hits.size() >= 1)
					{
						if (hits[0].collider->_gameObject == _gameObject)
							i = 1;
						if (i >= hits.size())
							continue ;
						if (hits[i].collider->_gameObject->isImmortal())
							continue;
						auto destroyable = hits[i].collider->_gameObject->GetComponent<Game::Component::Breakable>();
						auto bomb = hits[i].collider->_gameObject->GetComponent<Game::Component::Bomb>();
						if (destroyable)
							_gameObject->destroy(hits[i].collider->_gameObject);
						if (bomb)
							bomb->timer = 5.0f;
					}
				}
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
