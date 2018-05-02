#include "Game/Components/Bomb.hpp"
#include "Core/GameObject.hpp"

namespace Game
{
	namespace Component
	{
		Bomb::Bomb(BeerEngine::GameObject *gameObject) :
			Component(gameObject)
		{
			power = 1.0f;
        }

		void    Bomb::start(void)
		{
			render = _gameObject->GetComponent<BeerEngine::Component::MeshRenderer>();
		}

		void    Bomb::fixedUpdate(void)
		{

		}

		void    Bomb::update(void)
		{

		}

		void	Bomb::setPower(float pow)
		{
			power = pow;
		}
	}
}