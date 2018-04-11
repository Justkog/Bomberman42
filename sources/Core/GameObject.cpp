#include "Core/GameObject.hpp"

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