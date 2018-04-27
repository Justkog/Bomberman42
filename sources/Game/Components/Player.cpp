#include "Game/Components/Player.hpp"
#include "Game/Components/Character.hpp"
#include "Core/Input.hpp"


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
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_8))
				_character->translate(_transform.forward());
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_5))
				_character->translate(-_transform.forward());
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_4))
				_character->translate(_transform.left());
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_6))
				_character->translate(_transform.right());
        }
    }
}