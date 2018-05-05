#include "Game/Components/Breakable.hpp"

namespace Game
{
	namespace Component
	{

		Breakable::Breakable(BeerEngine::GameObject *gameObject):
		Component(gameObject),
		_transform(gameObject->transform),
		_posX(_transform.position.x),
		_posY(_transform.position.z)
		{ }

		Breakable::~Breakable(void)
		{
			destroyed();
		}

		void	Breakable::destroyed()
		{
			onDestruction.emit(_posX, _posY);
		}
	}
}
