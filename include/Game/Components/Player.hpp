#ifndef BE_GAME_COMPONENT_PLAYER_HPP
#define BE_GAME_COMPONENT_PLAYER_HPP 1

#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/GameObject.hpp"

namespace Game
{
	namespace Component
	{
		class Player : public BeerEngine::Component::Component, BeerEngine::Component::IUpdate
		{
		protected:


		public:
            Player(BeerEngine::GameObject *gameObject);

            virtual void    fixedUpdate(void);
       		virtual void    update(void);
		};
	}
}

#endif