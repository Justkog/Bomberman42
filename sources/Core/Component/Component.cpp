#include "Core/Component/Component.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		Component::Component(GameObject *gameObject) :
			_gameObject(gameObject)
		{

		}

		void    Component::destroy(GameObject *go)
		{
			if (go == nullptr)
				_gameObject->destroy(_gameObject);
			else
				_gameObject->destroy(go);
		}
	}
}