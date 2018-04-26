#include "Game/Components/Player.hpp"
#include "Core/Input.hpp"
#include "Core/Time.hpp"
#include "Core/GameObject.hpp"
#include "Core/Component/MeshRenderer.hpp"


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
				this->_transform->translate(this->_transform->forward() * BeerEngine::Time::GetDeltaTime());
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_5))
				this->_transform->translate(-this->_transform->forward() * BeerEngine::Time::GetDeltaTime());
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_4))
				this->_transform->translate(-this->_transform->right() * BeerEngine::Time::GetDeltaTime());
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_6))
				this->_transform->translate(-this->_transform->left() * BeerEngine::Time::GetDeltaTime());
        }

        void   Player::onTriggerStay(void)
        {
            // _gameObject->GetComponent<BeerEngine::Component::MeshRenderer>()
			// 		->getMaterial()->setColor(glm::vec4(1, 0, 0, 1));
        }

        void   Player::onTriggerEnter(void)
        {
            _gameObject->GetComponent<BeerEngine::Component::MeshRenderer>()
					->getMaterial()->setColor(glm::vec4(1, 0, 0, 1));
        }

        void   Player::onTriggerExit(void)
        {
            _gameObject->GetComponent<BeerEngine::Component::MeshRenderer>()
				->getMaterial()->setColor(glm::vec4(1, 1, 1, 1));
        }
    }
}