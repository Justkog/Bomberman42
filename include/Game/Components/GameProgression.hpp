// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef GAMEPROGRESSION_HPP
# define GAMEPROGRESSION_HPP

/*!
 * \file GameProgression.hpp
 * \brief Chargeur / Enregistreur de progression de jeu
 * \author jblondea
 */

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/Component.hpp"

namespace Game
{	
	class GameProgressionContainer
	{
		public:
			std::vector<std::string>	unlockedLevels;
	};

	namespace Component	{		
		class GameProgression : public BeerEngine::Component::Component, public BeerEngine::Component::IStart
		{
		private:
			static GameProgression * instance;

		public:
			AudioManager	*audioManager;

			// GameProgression( void );
			// GameProgression( GameProgression const & src );
			GameProgression(BeerEngine::GameObject *gameObject);
			virtual ~GameProgression( void );

			GameProgression & operator=( GameProgression const & rhs );

			void loadGameProgression();
			void saveGameProgression();
			void resetGameProgression();
			void applyCurrentGameProgression();
			void gatherCurrentGameProgression();
			void start(void);

			static GameProgressionContainer defaultGameProgression();
			static GameProgression & GetInstance();

			REGISTER_COMPONENT_HPP

			std::string filePath;
			Game::GameProgressionContainer gameProgressionContainer;

			Signal<> onChange;
		};
	};
};

std::ostream & operator<<(std::ostream & o, Game::Component::GameProgression const & i);

#endif
