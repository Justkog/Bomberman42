#include "Game/Components/GameManager.hpp"
#include "Core/Input.hpp"
#include "Core/Time.hpp"
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
		inGameMenu->setActive(!inGameMenu->_isActive);
}

void GameManager::fixedUpdate()
{
	
}

void GameManager::setPause(bool state)
{
	if (state)
	{
		BeerEngine::Time::gameSpeed = 0.0f;
		std::cout << "pausing game" << std::endl;
	}
	else
	{
		BeerEngine::Time::gameSpeed = 1.0f;
		std::cout << "resuming game" << std::endl;
	}
}

nlohmann::json	GameManager::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
		{"inGameMenu", SERIALIZE_BY_ID(inGameMenu)},
	});
	return j;
}

void GameManager::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
	DESERIALIZE_BY_ID(this->inGameMenu, InGameMenu, "inGameMenu", loader);
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
