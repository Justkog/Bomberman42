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
			render = _gameObject->AddComponent<BeerEngine::Component::MeshRenderer>();
			render->setMesh(BeerEngine::Graphics::Graphics::cube);
		}

		void    Bomb::fixedUpdate(void)
		{
			timer += 1.0f / 60.0f;

			if (timer >= 5.0f)
			{
				if (render != nullptr)
				{
					BeerEngine::Component::ParticleExplode *playerParticule = _gameObject->AddComponent<BeerEngine::Component::ParticleExplode>();
					playerParticule->setTexture(Assets::GetTexture("assets/textures/ParticleAtlas.png"));
					playerParticule->setAnimate(true, 64, 8, 8);
					playerParticule->setLifeTime(0.5f);
					playerParticule->setSize(1.0f, 2.0f);
					playerParticule->setSpawnTime(1.0f / 120.0f);

					// float sizeDeflag = power + 0.25f;

					// auto playerDeflag0 = _gameObject->AddComponent<BeerEngine::Component::ParticleBase>();
					// playerDeflag0->setTexture(Assets::GetTexture("assets/textures/ParticleAtlas.png"));
					// playerDeflag0->setColor(glm::vec4(1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
					// playerDeflag0->setAnimate(true, 64, 8, 8);
					// playerDeflag0->setLifeTime(1.0f);
					// playerDeflag0->setSize(2.0f, 1.0f);
					// playerDeflag0->setSpawnTime(1.0f / 120.0f);
					// playerDeflag0->setVelocity(glm::vec3(sizeDeflag, 0.0f, 0.0f));

					// auto playerDeflag1 = _gameObject->AddComponent<BeerEngine::Component::ParticleBase>();
					// playerDeflag1->setTexture(Assets::GetTexture("assets/textures/ParticleAtlas.png"));
					// playerDeflag1->setColor(glm::vec4(1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
					// playerDeflag1->setAnimate(true, 64, 8, 8);
					// playerDeflag1->setLifeTime(1.0f);
					// playerDeflag1->setSize(2.0f, 1.0f);
					// playerDeflag1->setSpawnTime(1.0f / 120.0f);
					// playerDeflag1->setVelocity(glm::vec3(-sizeDeflag, 0.0f, 0.0f));

					// auto playerDeflag2 = _gameObject->AddComponent<BeerEngine::Component::ParticleBase>();
					// playerDeflag2->setTexture(Assets::GetTexture("assets/textures/ParticleAtlas.png"));
					// playerDeflag2->setColor(glm::vec4(1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
					// playerDeflag2->setAnimate(true, 64, 8, 8);
					// playerDeflag2->setLifeTime(1.0f);
					// playerDeflag2->setSize(2.0f, 1.0f);
					// playerDeflag2->setSpawnTime(1.0f / 120.0f);
					// playerDeflag2->setVelocity(glm::vec3(0.0f, 0.0f, sizeDeflag));

					// auto playerDeflag3 = _gameObject->AddComponent<BeerEngine::Component::ParticleBase>();
					// playerDeflag3->setTexture(Assets::GetTexture("assets/textures/ParticleAtlas.png"));
					// playerDeflag3->setColor(glm::vec4(1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
					// playerDeflag3->setAnimate(true, 64, 8, 8);
					// playerDeflag3->setLifeTime(1.0f);
					// playerDeflag3->setSize(2.0f, 1.0f);
					// playerDeflag3->setSpawnTime(1.0f / 120.0f);
					// playerDeflag3->setVelocity(glm::vec3(0.0f, 0.0f, -sizeDeflag));

					_gameObject->destroy(render);
					render = nullptr;
				}
				else if (timer >= 10.0f)
					_gameObject->destroy(_gameObject);
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