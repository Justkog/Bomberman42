#ifndef BE_GAME_COMPONENT_BOMB_HPP
#define BE_GAME_COMPONENT_BOMB_HPP 1

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/ParticleBase.hpp"
#include "Core/Component/ParticleExplode.hpp"
#include "Core/Component/MeshRenderer.hpp"

namespace Game
{
	namespace Component
	{
		class Bomb : public BeerEngine::Component::Component,
			public BeerEngine::Component::IStart,
			public BeerEngine::Component::IUpdate
		{
		protected:
			BeerEngine::Component::MeshRenderer		*render;
			float								power;

		public:
            Bomb(BeerEngine::GameObject *gameObject);
			virtual void    start(void);
            virtual void    fixedUpdate(void);
       		virtual void    update(void);
			
			void			setPower(float pow);
		};
	}
}

#endif