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
#include "Game/Components/GameProgression.hpp"
#include "Game/Components/CameraController.hpp"
#include "Game/Components/LevelInstructions.hpp"

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

GameManager::GameManager ( void )
{
	return ;
}

GameManager::GameManager ( GameManager const & src )
{
	*this = src;
	return ;
}

GameManager &				GameManager::operator=( GameManager const & rhs )
{
	(void) rhs;
	if (this != &rhs)
	{}
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
_gameStarted(false),
gameOverMenu(nullptr),
victoryMenu(nullptr),
levelInstructions(nullptr),
storyMode(false),
victoryRoutine(nullptr),
isVictorious(false)
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
	{
		startVictory();
	}
}

void GameManager::registerEnemy(Breakable *enemyBreakable)
{
	enemyBreakables.push_back(enemyBreakable);
	enemyBreakable->onDestructionSelf.bind(&GameManager::acknowledgeEnemyDestruction, this);
}

void GameManager::setGameOver(glm::vec3 pos, int value)
{
	(void) pos;
	(void) value;
	if (isVictorious || !_gameStarted)
		return;
	if (victoryRoutine)
		stopRoutine(victoryRoutine);
	if (inGameMenu->_isActive)
		inGameMenu->setActive(!inGameMenu->_isActive);
	// std::cout << "game over" << std::endl;
	gameOverMenu->setActive(true);
	if (victoryMenu->_isActive)
	{
		victoryMenu->setActive(false);
		std::cout << "not a victory after all" << std::endl;
	}
	else
		onGameEnd.emit();
}

void GameManager::startVictory()
{
	std::cout << "victory" << std::endl;
	victoryRoutine = createVictoryRoutine();
	startRoutine(*victoryRoutine);
}

void GameManager::setVictory()
{
	if (inGameMenu->_isActive)
		inGameMenu->setActive(!inGameMenu->_isActive);
	onGameEnd.emit();
	victoryMenu->setActive(true);
}

void GameManager::save()
{
	auto start = gameProgression->gameProgressionContainer.unlockedLevels.begin();
	auto end = gameProgression->gameProgressionContainer.unlockedLevels.end();
	auto unlockedLevel = std::find(start, end, victoryMenu->sceneLoader.name);
	if (unlockedLevel == end)
	{
		gameProgression->gameProgressionContainer.unlockedLevels.push_back(victoryMenu->sceneLoader.name);
		gameProgression->saveGameProgression();
	}
}

BeerEngine::BeerRoutine::BeerRoutine *GameManager::createStartTimerRoutine()
{
	auto routine = &BeerEngine::BeerRoutine::BeerRoutine::CreateRoutine()
	.addAction([this] () {
		auto cc = this->_gameObject->GetComponent<CameraController>();
		if (cc)
			cc->animationStart();
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
		if (levelInstructions)
			levelInstructions->startInstructions();
		return true;
	})
	;
	return routine;
}

BeerEngine::BeerRoutine::BeerRoutine *GameManager::createVictoryRoutine()
{
	auto routine = &BeerEngine::BeerRoutine::BeerRoutine::CreateRoutine()
	.addAction([this] () {
		if (this->gameSpeed < 1.0f)
			this->isVictorious = true;
		this->gameSpeed -= 0.5f * (BeerEngine::Time::GetRealDeltaTime() + BeerEngine::Time::GetDeltaTime()) / 2;
		if (this->gameSpeed < 0)
		{
			this->gameSpeed = 0;
			setVictory();
			return true;
		}
		BeerEngine::Time::gameSpeed = this->gameSpeed;
		return false;
	})
	;
	return routine;
}


void GameManager::startGame()
{
	_gameStarted = true;
	timeUI->startClock();
	onGameStart.emit();
}

void GameManager::start()
{
	std::cout << "GameManager start" << std::endl;
	// playerDeathBinding = Binding::create(playerBreakable, this);
	// playerBreakable->add_binding(playerDeathBinding);
	playerBreakable->onDestruction.bind(&GameManager::setGameOver, this);
	startRoutine(*createStartTimerRoutine());
	this->gameSpeed = 1.0f;
}

void GameManager::update()
{
	BeerEngine::BeerRoutine::ARoutineRunner::update();
	if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::ESCAPE))
	{
		if (!victoryMenu->_isActive && !gameOverMenu->_isActive)
			inGameMenu->setActive(!inGameMenu->_isActive);
	}
	// if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::V))
	// {
	// 	startRoutine(*createVictoryRoutine());
	// }
}

void GameManager::fixedUpdate()
{

}

void GameManager::setPause(bool state)
{
	if (state)
	{
		onGamePause.emit();
		audioManager->pause();
		std::cout << "pausing game" << std::endl;
		BeerEngine::Time::gameSpeed = 0.0f;
	}
	else
	{
		onGameResume.emit();
		audioManager->continuePlaying();
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
