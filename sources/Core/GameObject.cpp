#include "Core/GameObject.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IRender.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/ACollider.hpp"
#include "Core/Transform.hpp"
#include "Core/Json/Json.hpp"

namespace BeerEngine
{
    GameObject::GameObject(int uniqueID) :
		_uniqueID(uniqueID)
	{
	}

	GameObject::~GameObject(void)
	{
		std::cout << "boom" << "\n";
		for (Component::Component *c : _components)
		{
			delete c;
		}
	}

	int		GameObject::getID()
	{
		return _uniqueID;
	}

	std::vector<Component::Component *> GameObject::GetComponents(void)
	{
		return _components;
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

	void    GameObject::componentPhysicUpdate(void)
	{
		for (Component::Component *c : _components)
		{
			if (auto *p = dynamic_cast<Component::ACollider*>(c))
				p->physicUpdate();
		}
	}

	nlohmann::json	GameObject::serialize()
	{
		return nlohmann::json {
            {"id", this->_uniqueID},
            {"name", this->name},
            {"transform", JsonSerializable::toSerializable(this->transform)},
            {"components", JsonSerializable::toSerializables<BeerEngine::Component::Component>(this->GetComponents())}
		};
	}

	// void GameObject::deserialize(const nlohmann::json & j)
    // {
    //     this->_uniqueID = j.at("id");
	// 	this->name = j.at("name");
    // }

	GameObject * GameObject::Deserialize(const nlohmann::json & j)
    {
		int id = j.at("id");
		auto go = new GameObject(id);
		go->name = j.at("name");
		go->transform = Transform::Deserialize(j.at("transform"));
		auto components = j.at("components");
        for (nlohmann::json::iterator it = components.begin(); it != components.end(); ++it) {
			std::cout << it.value() << "\n";
		}
		return go;
    }
}
