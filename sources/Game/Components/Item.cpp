#include "Game/Components/Map.hpp"
#include "Game/Components/Item.hpp"
#include "Game/Components/Player.hpp"
#include "Game/Components/Character.hpp"
#include "Core/Time.hpp"
#include "Core/GameObject.hpp"
#include "Core/Transform.hpp"
#include "Core/Component/ACollider.hpp"
#include "Core/Audio/AudioSource.hpp"
#include "Core/Audio/AudioClip.hpp"
#include "Game/Components/GameManager.hpp"

namespace Game
{
	namespace Component
	{
        Item::Item(BeerEngine::GameObject *gameObject) :
			Component(gameObject),
            _transform(_gameObject->transform)
		{
            _type = static_cast<Game::Component::ItemType>(glm::linearRand(0, static_cast<int>(ItemType::ExplosionBoost)));
        }

		Item::~Item()
		{
		}

        void    Item::onDestroy(void)
        {
			map->mapUpdate(_gameObject->transform.position, 0);
        }

        void    Item::start(void)
        {
            // auto meshRenderer = _gameObject->GetComponent<BeerEngine::Component::MeshRenderer>();
            // BeerEngine::Graphics::Texture *mapBlocTex;
            // BeerEngine::Graphics::AMaterial *mapBlocMat;

            // switch (_type)
            // {
            //     case ItemType::SpeedBoost:
            //         meshRenderer->setMesh("assets/models/Shoes/Shoes.obj");
            //         mapBlocTex = Assets::GetTexture("assets/models/Shoes/botafinal2-TM_u0_v0.png");
            //         mapBlocMat = new BeerEngine::Graphics::AMaterial(BeerEngine::Graphics::Graphics::defaultShader);
            //         mapBlocMat->setAlbedo(mapBlocTex);
            //         meshRenderer->setMaterial(mapBlocMat);
			//         _gameObject->transform.scale = glm::vec3(0.3, 0.3, 0.3);
            //         break;
            //     case ItemType::AddBomb:
            //         meshRenderer->setMesh("assets/models/Bomb/bomb.obj");
            //         mapBlocTex = Assets::GetTexture("assets/models/Bomb/bombbody_BaseColor.png");
            //         mapBlocMat = new BeerEngine::Graphics::AMaterial(BeerEngine::Graphics::Graphics::defaultShader);
            //         mapBlocMat->setAlbedo(mapBlocTex);
            //         meshRenderer->setMaterial(mapBlocMat);
			//         _gameObject->transform.scale = glm::vec3(0.3, 0.3, 0.3);
            //         break;
            //     case ItemType::ExplosionBoost:
            //         meshRenderer->setMesh("assets/models/Shoes/Shoes.obj");
            //         mapBlocTex = Assets::GetTexture("assets/models/Shoes/botafinal2-TM_u0_v0.png");
            //         mapBlocMat = new BeerEngine::Graphics::AMaterial(BeerEngine::Graphics::Graphics::defaultShader);
            //         mapBlocMat->setAlbedo(mapBlocTex);
            //         meshRenderer->setMaterial(mapBlocMat);
			//         _gameObject->transform.scale = glm::vec3(0.3, 0.3, 0.3);
            //         break;
            // }
        }

        void    Item::fixedUpdate(void)
        {
        }

        void    Item::update(void)
        {
            static float time = 0;
            time += 0.8 * BeerEngine::Time::GetDeltaTime();
            _transform.rotation = glm::quat(glm::vec3(0, time, 0));
            // Pin in map item is present
            int v = map->getCaseValue(glm::vec2(_gameObject->transform.position.x, _gameObject->transform.position.y));
            if (v != B && v != I)
                map->mapUpdate(_gameObject->transform.position, I);
        }

        void   Item::onTriggerStay(BeerEngine::Component::ACollider *other)
        {
        }

        void   Item::onTriggerEnter(BeerEngine::Component::ACollider *other)
        {
            auto character = other->_gameObject->GetComponent<Game::Component::Character>();

            if (character)
            {
                switch (_type)
                {
                    case ItemType::SpeedBoost:
                        character->increaseSpeed(0.25);
                        this->destroy();
                        break;
                    case ItemType::AddBomb:
                        character->increaseMaxBomb();
                        this->destroy();
                        break;
                    case ItemType::ExplosionBoost:
                        character->increaseExplosionSize(1);
                        this->destroy();
                        break;
                    case ItemType::Antidote:
                        if (!map->hasBreakable())
                        {
                            GameManager::GetInstance().setVictory();
                            this->destroy();
                        }
                        break;
                }
            }
        }

        void   Item::onTriggerExit(BeerEngine::Component::ACollider *other)
        {
        }

        nlohmann::json	Item::serialize()
		{
			return nlohmann::json {
				{"componentClass", typeid(Item).name()},
				{"type", _type},
			};
		}

		void Item::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
            this->_type = j.at("type");
		}

		REGISTER_COMPONENT_CPP(Item)
    }
}
