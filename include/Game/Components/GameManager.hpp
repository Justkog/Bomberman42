// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef GAMEMANAGER_HPP
# define GAMEMANAGER_HPP

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"

namespace Game
{
	namespace Component
	{
		class GameManager : public BeerEngine::Component::Component, public BeerEngine::Component::IUpdate, public BeerEngine::Component::IStart
		{
		private:
			static GameManager * instance;

		public:
			InGameMenu *inGameMenu;

			// GameManager( void );
			// GameManager( GameManager const & src );
			GameManager(BeerEngine::GameObject *gameObject);

			virtual ~GameManager( void );

			GameManager & operator=( GameManager const & rhs );
			friend std::ostream & operator<<(std::ostream & o, GameManager const & i);

			virtual void start();
			virtual void update();
			virtual void fixedUpdate();

			void setPause(bool state);
	
			static GameManager & GetInstance();

			REGISTER_COMPONENT_HPP
		};

	};

};

#endif
