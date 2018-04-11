#include "Core/GameObject.hpp"
#include "Core/Component/Component.hpp"

namespace BeerEngine
{
    GameObject::GameObject(int uniqueID) :
		_uniqueID(uniqueID)
	{
	}

	GameObject::~GameObject(void)
	{
		for (Component::Component *c : _components)
		{
			delete c;
		}
	}
}