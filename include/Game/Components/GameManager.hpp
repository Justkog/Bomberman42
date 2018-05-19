// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef GAMEMANAGER_HPP
# define GAMEMANAGER_HPP

/*!
 * \file GameManager.hpp
 * \brief Manager qui suit et controle le déroulement d'une partie
 * \author jblondea
 */

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Audio/AudioSource.hpp"
#include "Core/Audio/AudioClip.hpp"
#include "Core/BeerRoutine/ARoutineRunner.hpp"
#include "Game/Components/AudioManager.hpp"

namespace Game
{
	namespace Component
	{
		class GameManager : public BeerEngine::Component::Component,
							public BeerEngine::Component::IUpdate,
							public BeerEngine::Component::IStart,
							public BeerEngine::BeerRoutine::ARoutineRunner
		{
		private:
			static GameManager * instance;

			GameManager();
			GameManager(const GameManager &val);
			GameManager & operator=( GameManager const & rhs );

		public:
			InGameMenu 					*inGameMenu;
			GameOverMenu				*gameOverMenu;
			VictoryMenu					*victoryMenu;
			Breakable					*playerBreakable;
			TimeUI						*timeUI;
			StartTimerUI				*startTimerUI;
			std::vector<Breakable *> 	enemyBreakables;
			AudioManager				*audioManager;
			bool						storyMode;

			GameManager(BeerEngine::GameObject *gameObject);
			virtual ~GameManager( void );

			friend std::ostream & operator<<(std::ostream & o, GameManager const & i);

			virtual void start();
			virtual void update();
			virtual void fixedUpdate();

			void startGame();
			void setPause(bool state);
			void setGameOver(glm::vec3 pos, int value);
			void setVictory();
			void acknowledgeEnemyDestruction(Breakable *enemyBreakable);

			void registerEnemy(Breakable *enemyBreakable);

			Signal<> onGameStart;
			Signal<> onGamePause;
			Signal<> onGameResume;
			Signal<> onGameEnd;

			BeerEngine::BeerRoutine::BeerRoutine *createStartTimerRoutine();

			static GameManager & GetInstance();

			REGISTER_COMPONENT_HPP
		};

	};

};

#endif
