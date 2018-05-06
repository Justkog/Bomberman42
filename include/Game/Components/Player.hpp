#ifndef BE_GAME_COMPONENT_PLAYER_HPP
#define BE_GAME_COMPONENT_PLAYER_HPP 1

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
						public BeerEngine::Component::IUI
		{
		protected:
			BeerEngine::Transform	&_transform;
			Game::Component::Character *_character;

		public:
            Player(BeerEngine::GameObject *gameObject);

            virtual void    start(void);
            virtual void    fixedUpdate(void);
       		virtual void    update(void);
			virtual void    renderUI(struct nk_context *ctx);
       		// virtual void    onTriggerStay(BeerEngine::Component::ACollider *other);
       		// virtual void    onTriggerEnter(BeerEngine::Component::ACollider *other);
       		// virtual void    onTriggerExit(BeerEngine::Component::ACollider *other);
       		// virtual void    onColliderStay(BeerEngine::Component::ACollider *other);
       		// virtual void    onColliderEnter(BeerEngine::Component::ACollider *other);
       		// virtual void    onColliderExit(BeerEngine::Component::ACollider *other);

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);

			REGISTER_COMPONENT_HPP

			Signal<float, float> createCrateSignal;

			BeerEngine::Audio::AudioSource      srcAudio;
			// BeerEngine::Audio::AudioSource      srcAudio2(ALuint);

		};
	}
}

#endif
