#ifndef BE_GAME_COMPONENT_BOMB_HPP
#define BE_GAME_COMPONENT_BOMB_HPP 1

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/MeshRenderer.hpp"
#include "Core/Component/IColliderExit.hpp"
#include "Core/Component/ACollider.hpp"

namespace Game
{
	namespace Component
	{
		class Bomb : public BeerEngine::Component::Component,
			public BeerEngine::Component::IStart,
			public BeerEngine::Component::IUpdate,
			public BeerEngine::Component::IColliderExit
		{
		protected:
			BeerEngine::Component::MeshRenderer		*render;
			float	timer;

		public:
            Bomb(BeerEngine::GameObject *gameObject);
			virtual ~Bomb(void);

			virtual void    start(void);
            virtual void    fixedUpdate(void);
       		virtual void    update(void);
       		virtual void    onColliderExit(BeerEngine::Component::ACollider *other);
			void			explode(void);
			
			void			setPower(float pow);

			static std::vector<Bomb*> bombs;
			Game::Component::Map *map;
			float power;

			static BeerEngine::Graphics::Texture *explosionTexture;
		};
	}
}

#endif