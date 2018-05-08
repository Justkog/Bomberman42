#include "Game/Components/SettingsMenu.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*SettingsMenu::SettingsMenu ( void )
{
	return ;
}*/

/*SettingsMenu::SettingsMenu ( SettingsMenu const & src )
{
	*this = src;
	return ;
}*/

SettingsMenu &				SettingsMenu::operator=( SettingsMenu const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

SettingsMenu::~SettingsMenu ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

SettingsMenu::SettingsMenu(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, SettingsMenu const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void SettingsMenu::start()
{
	std::cout << "SettingsMenu start" << std::endl;
}

void SettingsMenu::update()
{
	
}

void SettingsMenu::fixedUpdate()
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
