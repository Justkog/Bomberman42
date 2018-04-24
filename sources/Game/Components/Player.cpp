#include "Game/Components/Player.hpp"
#include "Core/Input.hpp"
#include "Core/Time.hpp"

namespace Game
{
	namespace Component
	{
        Player::Player(BeerEngine::GameObject *gameObject) :
			Component(gameObject)
		{

        }

        void    Player::start(void)
        {
            _transform = &(this->_gameObject->transform);
        }

        void    Player::fixedUpdate(void)
        {
            
        }

        void    Player::update(void)
        {
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_8))
            {
				this->_transform->translate(this->_transform->forward() * BeerEngine::Time::GetDeltaTime());
            }
        }
    }
}