#ifndef BE_GAME_COMPONENT_BOMB_HPP
#define BE_GAME_COMPONENT_BOMB_HPP 1

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/MeshRenderer.hpp"
#include "Core/Component/IColliderExit.hpp"
#include "Core/Component/ITriggerEnter.hpp"
#include "Core/Component/ACollider.hpp"

/*!
 * \file Bomb.hpp
 * \brief Component bomb, ça fait boum quoi
 * \author mgallo,stmartin,qhonore
 */
namespace Game
{
	namespace Component
	{
		/*! \class Bomb
		* \brief La classe Bomb gère la range, le timer et l'explosion des bombes...
		*/
		class Bomb : public BeerEngine::Component::Component,
			public BeerEngine::Component::IStart,
			public BeerEngine::Component::IUpdate,
			public BeerEngine::Component::IColliderExit

		{
		protected:
			BeerEngine::Component::MeshRenderer		*render;
			float	timer;

			glm::vec3	*hitDir;

		private:
			Bomb();
			Bomb(const Bomb &val);
			Bomb &operator=(const Bomb &val);

		public:
            Bomb(BeerEngine::GameObject *gameObject);
			virtual ~Bomb(void);

			virtual void    start(void);
            virtual void    fixedUpdate(void);
       		virtual void    update(void);
       		virtual void    onColliderExit(BeerEngine::Component::ACollider *other);
			void			explodeToward(glm::vec3 dir, int hitIDStorage);
			void			explode(void);
			void			explodeTowardUpdateMap(int value);
			void			explodeUpdateMap(void);
			
			void			setPower(float pow);

			static std::vector<Bomb*> bombs;
			Game::Component::Map *map;
			float power;

			static BeerEngine::Graphics::Texture *explosionTexture;
			Signal<> onExplode;
		};
	}
}

#endif