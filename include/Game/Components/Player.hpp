#ifndef BE_GAME_COMPONENT_PLAYER_HPP
#define BE_GAME_COMPONENT_PLAYER_HPP 1

#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/ITriggerStay.hpp"
#include "Core/Component/ITriggerEnter.hpp"
#include "Core/Component/ITriggerExit.hpp"
#include "Core/Component/IColliderStay.hpp"
#include "Core/Component/IColliderEnter.hpp"
#include "Core/Component/IColliderExit.hpp"
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
						public BeerEngine::Component::ITriggerExit, 
						public BeerEngine::Component::IColliderStay,
						public BeerEngine::Component::IColliderEnter,
						public BeerEngine::Component::IColliderExit
		{
		protected:
			BeerEngine::Transform	*_transform;

		public:
            Player(BeerEngine::GameObject *gameObject);

            virtual void    start(void);
            virtual void    fixedUpdate(void);
       		virtual void    update(void);
       		virtual void    onTriggerStay(BeerEngine::Component::ACollider *other);
       		virtual void    onTriggerEnter(BeerEngine::Component::ACollider *other);
       		virtual void    onTriggerExit(BeerEngine::Component::ACollider *other);
       		virtual void    onColliderStay(BeerEngine::Component::ACollider *other);
       		virtual void    onColliderEnter(BeerEngine::Component::ACollider *other);
       		virtual void    onColliderExit(BeerEngine::Component::ACollider *other);
		};
	}
}

#endif