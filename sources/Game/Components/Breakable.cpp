#include "Game/Components/Breakable.hpp"


namespace Game
{
	namespace Component
	{
		Breakable::Breakable(BeerEngine::GameObject *gameObject):
		Component(gameObject),
		_transform(gameObject->transform)
		_posX(_transform->position),
		_posY(y)
		{ }
	}
}
