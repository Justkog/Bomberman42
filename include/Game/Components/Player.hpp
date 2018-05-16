#ifndef BE_GAME_COMPONENT_PLAYER_HPP
#define BE_GAME_COMPONENT_PLAYER_HPP 1

/*!
 * \file Player.hpp
 * \brief Component de contrôle du joueur.
 * \author jblondea, qhonore, stmartin
 */

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/ITriggerStay.hpp"
#include "Core/Component/ITriggerEnter.hpp"
#include "Core/Component/ITriggerExit.hpp"
#include "Core/Component/IColliderStay.hpp"
#include "Core/Component/IColliderEnter.hpp"
#include "Core/Component/IColliderExit.hpp"
#include "Core/Component/IOnDestroy.hpp"
#include "Core/Component/IUI.hpp"
#include "Core/Audio/AudioSource.hpp"
#include "Core/Audio/AudioClip.hpp"

namespace Game
{
	namespace Component
	{
		class Character;

		class Player : public BeerEngine::Component::Component,
						public BeerEngine::Component::IStart,
						public BeerEngine::Component::IUpdate,
						public BeerEngine::Component::IUI,
						public BeerEngine::Component::IColliderEnter,
						public BeerEngine::Component::IOnDestroy

		{
		protected:
			BeerEngine::Transform				&_transform;
			bool								_gameStarted;

		public:
			Game::Component::Character 			*_character;
			BeerEngine::Audio::AudioSource      *srcAudio;
			BeerEngine::Audio::AudioSource      *itemSrcAudio;
			bool								play;

            Player(BeerEngine::GameObject *gameObject);
			virtual ~Player(void);

       		virtual void    onDestroy(void);
            virtual void    start(void);
            virtual void    fixedUpdate(void);
       		virtual void    update(void);
			virtual void    renderUI(struct nk_context *ctx);
       		// virtual void    onTriggerStay(BeerEngine::Component::ACollider *other);
       		// virtual void    onTriggerEnter(BeerEngine::Component::ACollider *other);
       		// virtual void    onTriggerExit(BeerEngine::Component::ACollider *other);
       		// virtual void    onColliderStay(BeerEngine::Component::ACollider *other);
       		virtual void    onColliderEnter(BeerEngine::Component::ACollider *other);
       		// virtual void    onColliderExit(BeerEngine::Component::ACollider *other);

			void		playStepSound();
			void 		startGame(void);


			REGISTER_COMPONENT_HPP

			Signal<float, float> createCrateSignal;
		};
	}
}

#endif
