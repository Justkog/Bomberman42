#ifndef AUDIOMANAGER_HPP
# define AUDIOMANAGER_HPP

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Audio/AudioSource.hpp"
#include "Core/Audio/AudioClip.hpp"

namespace Game
{
	namespace Component
	{
		class AudioManager : public BeerEngine::Component::Component
		{
		// private:
		// 	static GameManager * instance;

		public:
			// InGameMenu 					*inGameMenu;
			// GameOverMenu				*gameOverMenu;
			// VictoryMenu					*victoryMenu;
			// Breakable					*playerBreakable;
			// std::vector<Breakable *> 	enemyBreakables;
      AudioManager(BeerEngine::GameObject *gameObject);
      ~AudioManager(void);

			BeerEngine::Audio::AudioSource      srcAudio;

			// virtual void start();
			// virtual void update();
			// virtual void fixedUpdate();
      //
			// void setPause(bool state);
			// void setGameOver(glm::vec3 pos, int value);
			// void setVictory();
			// void acknowledgeEnemyDestruction(Breakable *enemyBreakable);
      //
			// void registerEnemy(Breakable *enemyBreakable);
      //
			// static GameManager & GetInstance();
      //
			REGISTER_COMPONENT_HPP
		};

	};

};

#endif
