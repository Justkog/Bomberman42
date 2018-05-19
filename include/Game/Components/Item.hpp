#ifndef BE_GAME_COMPONENT_ITEM_HPP
#define BE_GAME_COMPONENT_ITEM_HPP 1

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/ITriggerStay.hpp"
#include "Core/Component/ITriggerEnter.hpp"
#include "Core/Component/ITriggerExit.hpp"
#include "Core/Component/IOnDestroy.hpp"

/*!
 * \file Item.hpp
 * \brief Component d'item bonus à ramasser
 * \author qhonore
 */
namespace Game
{
	namespace Component
	{
		/*! \class Item
		* \brief La classe Item gère les bonus que l'on peut ramasser en jeu (bomb+, explosion+, vitesse...)
		*/
		class Item : public BeerEngine::Component::Component,
						public BeerEngine::Component::IStart,
						public BeerEngine::Component::IUpdate,
						public BeerEngine::Component::ITriggerStay,
						public BeerEngine::Component::ITriggerEnter,
						public BeerEngine::Component::ITriggerExit,
						public BeerEngine::Component::IOnDestroy
		{
		protected:

		public:
            Item(BeerEngine::GameObject *gameObject);
			~Item();
			
			virtual void    onDestroy(void);
            virtual void    start(void);
            virtual void    fixedUpdate(void);
       		virtual void    update(void);
       		virtual void    onTriggerStay(BeerEngine::Component::ACollider *other);
       		virtual void    onTriggerEnter(BeerEngine::Component::ACollider *other);
       		virtual void    onTriggerExit(BeerEngine::Component::ACollider *other);

			BeerEngine::Transform	&_transform;
			ItemType				_type;

			Game::Component::Map	*map;

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif
