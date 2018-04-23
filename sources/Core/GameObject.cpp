#include "Core/GameObject.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IRender.hpp"
#include "Core/Component/IStart.hpp"

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

	void	GameObject::start(void) {}
	void    GameObject::fixedUpdate(void) {}
	void    GameObject::update(void) {}
	void    GameObject::renderUpdate(void) {}
	void    GameObject::render(void) {}

	void    GameObject::componentStart(void)
	{
		for (Component::Component *c : _components)
		{
			if (Component::IStart *u = dynamic_cast<Component::IStart*>(c))
				u->start();
		}
	}

	void    GameObject::componentFixedUpdate(void)
	{
		for (Component::Component *c : _components)
		{
			if (Component::IUpdate *u = dynamic_cast<Component::IUpdate*>(c))
				u->fixedUpdate();
		}
	}

	void    GameObject::componentUpdate(void)
	{
		for (Component::Component *c : _components)
		{
			if (Component::IUpdate *u = dynamic_cast<Component::IUpdate*>(c))
				u->update();
		}
	}

	void    GameObject::componentRenderUpdate(void)
	{
		for (Component::Component *c : _components)
		{
			if (Component::IRender *r = dynamic_cast<Component::IRender*>(c))
				r->renderUpdate();
		}
	}

	void    GameObject::componentRender(void)
	{
		for (Component::Component *c : _components)
		{
			if (Component::IRender *r = dynamic_cast<Component::IRender*>(c))
				r->render();
		}
	}

}