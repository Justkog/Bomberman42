#include "Game/Components/Player.hpp"
#include "Game/Components/Character.hpp"
#include "Core/Input.hpp"
#include "Core/Component/RigidBody2D.hpp"

namespace Game
{
	namespace Component
	{
        Player::Player(BeerEngine::GameObject *gameObject) :
			Component(gameObject),
            _transform(gameObject->transform)
		{

        }

        void    Player::start(void)
        {
            _character = _gameObject->GetComponent<Game::Component::Character>();
        }

        void    Player::fixedUpdate(void)
        {
            
        }

        void    Player::update(void)
        {
            BeerEngine::Component::RigidBody2D *rb2d = _gameObject->GetComponent<BeerEngine::Component::RigidBody2D>();
            if (rb2d)
            {
                if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_8))
                    rb2d->velocity = glm::vec2(0, 2);
                if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_5))
                    rb2d->velocity = glm::vec2(0, -2);
                if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_4))
                    rb2d->velocity = glm::vec2(2, 0);
                if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_6))
                    rb2d->velocity = glm::vec2(-2, 0);
            }
            

            // if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_8))
            // {
            //     if (rb2d)
            //     {
            //         rb2d->velocity = glm::vec2(0, 5);
            //     }
            // }
				//_character->translate(_transform.forward());
            // if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_5))
			// 	_character->translate(-_transform.forward());
            // if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_4))
			// 	_character->translate(_transform.left());
            // if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_6))
			// 	_character->translate(_transform.right());
            if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::KP_0))
				this->destroy();
        }
    }
}