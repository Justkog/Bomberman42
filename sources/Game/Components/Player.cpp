#include "Game/Components/Player.hpp"
#include "Core/IO/FileUtils.hpp"

namespace Game
{
	namespace Component
	{
        Player::Player(BeerEngine::GameObject *gameObject) :
			Component(gameObject)
		{

        }

        void    Player::fixedUpdate(void)
        {
            std::cout << "test" << "\n";
        }

        void    Player::update(void)
        {
            std::cout << "test" << "\n";
        }
    }
}