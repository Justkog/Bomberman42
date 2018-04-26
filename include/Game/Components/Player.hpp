#ifndef BE_GAME_COMPONENT_PLAYER_HPP
#define BE_GAME_COMPONENT_PLAYER_HPP 1

#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/ITriggerStay.hpp"
#include "Core/Component/ITriggerEnter.hpp"
#include "Core/Component/ITriggerExit.hpp"
#include "Core/GameObject.hpp"
#include "Core/Transform.hpp"

namespace Game
{
	namespace Component
	{
		class Player : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart,
						public BeerEngine::Component::IUpdate, 
						public BeerEngine::Component::ITriggerStay,
						public BeerEngine::Component::ITriggerEnter,
						public BeerEngine::Component::ITriggerExit
		{
		protected:
			BeerEngine::Transform	*_transform;

		public:
            Player(BeerEngine::GameObject *gameObject);

            virtual void    start(void);
            virtual void    fixedUpdate(void);
       		virtual void    update(void);
       		virtual void    onTriggerStay(void);
       		virtual void    onTriggerEnter(void);
       		virtual void    onTriggerExit(void);
		};
	}
}

#endif