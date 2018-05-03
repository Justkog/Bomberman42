#include "Game/Components/Breakable.hpp"

namespace Game
{
	namespace Component
	{

		Breakable::Breakable(BeerEngine::GameObject *gameObject):
		Component(gameObject),
		_transform(gameObject->transform),
		_posX(_transform.position.x),
		_posY(_transform.position.y)
		{ }

		void	destroyed()
		{
			// _map.mapUpdate(_posX, _posY);
		}
	}
}
