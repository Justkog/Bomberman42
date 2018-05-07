#include "Game/Components/Item.hpp"
#include "Game/Components/Player.hpp"
#include "Game/Components/Character.hpp"
#include "Core/Time.hpp"
#include "Core/GameObject.hpp"
#include "Core/Transform.hpp"
#include "Core/Component/ACollider.hpp"
#include "Core/Audio/AudioSource.hpp"
#include "Core/Audio/AudioClip.hpp"

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

        void    Item::start(void)
        {
        }

        void    Item::fixedUpdate(void)
        {

        }

        void    Item::update(void)
        {
            static float time = 0;
            time += 0.3 * BeerEngine::Time::GetDeltaTime();
            _transform.rotation = glm::quat(glm::vec3(0, time, 0));
        }

        void   Item::onTriggerStay(BeerEngine::Component::ACollider *other)
        {
        }

        void   Item::onTriggerEnter(BeerEngine::Component::ACollider *other)
        {
            auto character = other->_gameObject->GetComponent<Game::Component::Character>();

			if (other->_gameObject->GetComponent<Game::Component::Player>())
			{
				BeerEngine::Audio::AudioClip   		clip("assets/sounds/item.wav");
				BeerEngine::Audio::AudioSource      srcAudio(clip.getBuffer());
				srcAudio.setPosition(_gameObject->transform.position.x, _gameObject->transform.position.y, _gameObject->transform.position.z);
				srcAudio.play();
			}
            if (character)
            {
                switch (_type)
                {
                    case ItemType::SpeedBoost:
                        character->increaseSpeed(0.25);
                        break;

                    case ItemType::AddBomb:
                        character->addBomb(1);
                        break;

                    case ItemType::ExplosionBoost:
                        character->increaseExplosionSize(1);
                        break;
                }
                this->destroy();
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

		void Item::deserialize(const nlohmann::json & j)
		{
            this->_type = j.at("type");
		}

		REGISTER_COMPONENT_CPP(Item)
    }
}
