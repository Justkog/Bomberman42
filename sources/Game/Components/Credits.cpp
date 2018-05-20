#include "Game/Components/Credits.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*Credits::Credits ( void )
{
	return ;
}*/

/*Credits::Credits ( Credits const & src )
{
	*this = src;
	return ;
}*/

Credits &				Credits::operator=( Credits const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Credits::~Credits ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

Credits::Credits(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, Credits const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void Credits::start()
{
	std::cout << "Credits start" << std::endl;
}

void Credits::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	
}

void Credits::renderUI(struct nk_context *ctx)
{
	// Game created by jblondea, mgallo, mploux, qhonore and stmartin
	// School 42 Project

	
}

nlohmann::json	Credits::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
	});
	return j;
}

void Credits::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
}

REGISTER_COMPONENT_CPP(Credits)

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
