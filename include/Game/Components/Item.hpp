#ifndef BE_GAME_COMPONENT_ITEM_HPP
#define BE_GAME_COMPONENT_ITEM_HPP 1

#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/ITriggerStay.hpp"
#include "Core/Component/ITriggerEnter.hpp"
#include "Core/Component/ITriggerExit.hpp"
#include "Core/GameObject.hpp"
#include "Core/Transform.hpp"

#define MAX_SPEED 4

namespace Game
{
	namespace Component
	{
		enum ItemType { SpeedBoost, Bomb, ExplosionBoost };

		class Item : public BeerEngine::Component::Component,
						public BeerEngine::Component::IStart,
						public BeerEngine::Component::IUpdate,
						public BeerEngine::Component::ITriggerStay,
						public BeerEngine::Component::ITriggerEnter,
						public BeerEngine::Component::ITriggerExit
		{
		protected:

		public:
            Item(BeerEngine::GameObject *gameObject);

            virtual void    start(void);
            virtual void    fixedUpdate(void);
       		virtual void    update(void);
       		virtual void    onTriggerStay(BeerEngine::Component::ACollider *other);
       		virtual void    onTriggerEnter(BeerEngine::Component::ACollider *other);
       		virtual void    onTriggerExit(BeerEngine::Component::ACollider *other);

			BeerEngine::Transform	&_transform;
			ItemType				_type;
		};
	}
}

#endif