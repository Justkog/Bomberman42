#include "Game/Components/Item.hpp"
#include "Game/Components/Player.hpp"
#include "Core/Time.hpp"
#include "Core/GameObject.hpp"
#include "Core/Transform.hpp"
#include "Core/Component/ACollider.hpp"

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
            auto go = other->_gameObject->GetComponent<Player>();

            if (go)
            {
                std::cout << "Player on me !!!\n";
            }
        }

        void   Item::onTriggerExit(BeerEngine::Component::ACollider *other)
        {
        }
    }
}