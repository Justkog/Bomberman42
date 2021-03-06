#include "Game/Input.hpp"

namespace Game
{
	std::map<std::string, BeerEngine::KeyCode> setDefaultKeyBindings()
	{
		std::map<std::string, BeerEngine::KeyCode> defaultBindings;
		defaultBindings["move up"] = BeerEngine::KeyCode::KP_8;
		defaultBindings["move down"] = BeerEngine::KeyCode::KP_5;
		defaultBindings["move left"] = BeerEngine::KeyCode::KP_4;
		defaultBindings["move right"] = BeerEngine::KeyCode::KP_6;
		defaultBindings["bomb"] = BeerEngine::KeyCode::SPACE;
		return defaultBindings;
	}

	std::map<std::string, BeerEngine::KeyCode> Input::keyBindings = setDefaultKeyBindings();

	Input::Input ( void )
	{
		return ;
	}

	Input::Input ( Input const & src )
	{
		*this = src;
		return ;
	}

	Input &				Input::operator=( Input const & rhs )
	{
		if (this != &rhs)
		{
			// make stuff
		}
		return (*this);
	}

	Input::~Input ( void )
	{
		return ;
	}

	std::ostream &				operator<<(std::ostream & o, Input const & i)
	{
		(void)i;
		return (o);
	}
}