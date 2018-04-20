#include "Game/Components/Settings.hpp"
#include <iostream>

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Game::Component::Settings::Settings ( void )
{
	return ;
}

Game::Component::Settings::Settings ( Game::Component::Settings const & src )
{
	*this = src;
	return ;
}

Game::Component::Settings &				Game::Component::Settings::operator=( Game::Component::Settings const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Game::Component::Settings::~Settings ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, Game::Component::Settings const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void Game::Component::Settings::loadSettings() {
	std::cout << "loading settings" << "\n";
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
