#include "Game/Components/GameManager.hpp"
#include "Core/Input.hpp"
#include "Core/Time.hpp"
#include "Core/BeerRoutine/BeerRoutine.hpp"
#include "Game/Components/InGameMenu.hpp"
#include "Game/Components/GameOverMenu.hpp"
#include "Game/Components/VictoryMenu.hpp"
#include "Game/Components/TimeUI.hpp"
#include "Game/Components/Breakable.hpp"
#include "Game/Components/StartTimerUI.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

GameManager * GameManager::instance = nullptr;

GameManager & GameManager::GetInstance()
{
	return *GameManager::instance;
}

// ###############################################################

// CANONICAL #####################################################

/*GameManager::GameManager ( void )
{
	return ;
}*/

/*GameManager::GameManager ( GameManager const & src )
{
	*this = src;
	return ;
}*/

GameManager &				GameManager::operator=( GameManager const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

GameManager::~GameManager ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

GameManager::GameManager(BeerEngine::GameObject *gameObject) :
Component(gameObject),
gameOverMenu(nullptr),
victoryMenu(nullptr)
{
	instance = this;
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, GameManager const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void GameManager::acknowledgeEnemyDestruction(Breakable *enemyBreakable)
{
	std::cout << "enemy destroyed!" << std::endl;
	auto it = std::find(enemyBreakables.begin(), enemyBreakables.end(), enemyBreakable);
	if (it != enemyBreakables.end())
		enemyBreakables.erase(it);
	if (enemyBreakables.size() == 0)
		setVictory();
}

void GameManager::registerEnemy(Breakable *enemyBreakable)
{
	enemyBreakables.push_back(enemyBreakable);
	enemyBreakable->onDestructionSelf.bind(&GameManager::acknowledgeEnemyDestruction, this);
}

void GameManager::setGameOver(glm::vec3 pos, int value)
{
	// srcAudio->Delete();
	std::cout << "game over" << std::endl;
	gameOverMenu->setActive(true);
	if (victoryMenu->_isActive)
	{
		victoryMenu->setActive(false);
		std::cout << "not a victory after all" << std::endl;
	}
}

void GameManager::setVictory()
{
	std::cout << "victory" << std::endl;
	victoryMenu->setActive(true);
}

BeerEngine::BeerRoutine::BeerRoutine *GameManager::createStartTimerRoutine()
{
	auto routine = &BeerEngine::BeerRoutine::BeerRoutine::CreateRoutine()
	.addAction([this] () {
		this->startTimerUI->updateDisplay("Ready?");
		return true;
	})
	.addTimer(2.0f)
	.addAction([&] () {
		this->startTimerUI->updateDisplay("3");
		return true;
	})
	.addTimer(1.0f)
	.addAction([&] () {
		this->startTimerUI->updateDisplay("2");
		return true;
	})
	.addTimer(1.0f)
	.addAction([&] () {
		this->startTimerUI->updateDisplay("1");
		return true;
	})
	.addTimer(1.0f)
	.addAction([this] () {
		this->startTimerUI->updateDisplay("Go !");
		this->startGame();
		return true;
	})
	.addTimer(1.0f)
	.addAction([this] () {
		this->startTimerUI->setActive(false);
		return true;
	})
	;
	return routine;
}

void GameManager::startGame()
{
	timeUI->startClock();
	onGameStart.emit();
}

void GameManager::start()
{
	std::cout << "GameManager start" << std::endl;
	playerBreakable->onDestruction.bind(&GameManager::setGameOver, this);
	startRoutine(*createStartTimerRoutine());
}

void GameManager::update()
{
	BeerEngine::BeerRoutine::ARoutineRunner::update();
	if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::ESCAPE))
		inGameMenu->setActive(!inGameMenu->_isActive);
	if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::V))
		victoryMenu->setActive(true);
}

void GameManager::fixedUpdate()
{

}

void GameManager::setPause(bool state)
{
	if (state)
	{
		std::cout << "pausing game" << std::endl;
		BeerEngine::Time::gameSpeed = 0.0f;
	}
	else
	{
		std::cout << "resuming game" << std::endl;
		BeerEngine::Time::gameSpeed = 1.0f;
	}
}

nlohmann::json	GameManager::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
		{"inGameMenu", SERIALIZE_BY_ID(inGameMenu)},
		{"gameOverMenu", SERIALIZE_BY_ID(gameOverMenu)},
		{"victoryMenu", SERIALIZE_BY_ID(victoryMenu)},
		{"playerBreakable", SERIALIZE_BY_ID(playerBreakable)},
	});
	return j;
}

void GameManager::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
	DESERIALIZE_BY_ID(this->inGameMenu, InGameMenu, "inGameMenu", loader);
	DESERIALIZE_BY_ID(this->gameOverMenu, GameOverMenu, "gameOverMenu", loader);
	DESERIALIZE_BY_ID(this->victoryMenu, VictoryMenu, "victoryMenu", loader);
	DESERIALIZE_BY_ID(this->playerBreakable, Breakable, "playerBreakable", loader);
}

REGISTER_COMPONENT_CPP(GameManager)

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
	}
}
