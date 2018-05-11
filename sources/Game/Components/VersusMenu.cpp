#include "Game/Components/VersusMenu.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*VersusMenu::VersusMenu ( void )
{
	return ;
}*/

/*VersusMenu::VersusMenu ( VersusMenu const & src )
{
	*this = src;
	return ;
}*/

VersusMenu &				VersusMenu::operator=( VersusMenu const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

VersusMenu::~VersusMenu ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

VersusMenu::VersusMenu(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, VersusMenu const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void VersusMenu::start()
{
	std::cout << "VersusMenu start" << std::endl;
	maps.push_back({"level 1", "assets/scene/level1.scene"});
	maps.push_back({"level 2", "assets/scene/level2.scene"});
	maps.push_back({"level 3", "assets/scene/level3.scene"});
}

void VersusMenu::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	
}

void VersusMenu::renderUI(struct nk_context *ctx)
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
