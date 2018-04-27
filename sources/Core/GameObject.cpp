#include "Core/GameObject.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IRender.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/ACollider.hpp"
#include "Core/AScene.hpp"

namespace BeerEngine
{
    GameObject::GameObject(int uniqueID, AScene &scene) :
		_uniqueID(uniqueID),
		_scene(scene)
	{
	}

	GameObject::~GameObject(void)
	{
		std::cout << "destroying : " << this->name << std::endl;
		for (Component::Component *c : _components)
		{
			std::cout << "destroying component : " << c << std::endl;
			delete c;
		}
		_components.clear();
	}

	void	GameObject::start(void) {}
	void    GameObject::fixedUpdate(void) {}
	void    GameObject::update(void) {}
	void    GameObject::renderUpdate(void) {}
	void    GameObject::render(void) {}

	void    GameObject::destroy(GameObject *go)
    {
        _scene.destroy(go);
    }

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

	void    GameObject::componentPhysicUpdate(void)
	{
		for (Component::Component *c : _components)
		{
			if (auto *p = dynamic_cast<Component::ACollider*>(c))
				p->physicUpdate();
		}
	}

}
