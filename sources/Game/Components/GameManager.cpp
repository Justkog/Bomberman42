#include "Game/Components/GameManager.hpp"
#include "Core/Input.hpp"
#include "Game/Components/InGameMenu.hpp"

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
Component(gameObject)
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


void GameManager::start()
{
	std::cout << "GameManager start" << std::endl;
}

void GameManager::update()
{
	if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::ESCAPE))
	{
		std::cout << "escape pushed" << std::endl;
		if (inGameMenu->_isActive)
			inGameMenu->setActive(false);
		else
			inGameMenu->setActive(true);
	}
}

void GameManager::fixedUpdate()
{
	
}

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
