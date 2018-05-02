#include "Core/GameObject.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IRender.hpp"
#include "Core/Component/IRenderAlpha.hpp"
#include "Core/Component/IUI.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/ACollider.hpp"
#include "Core/Transform.hpp"
#include "Core/Component/RigidBody2D.hpp"
#include "Core/Json/Json.hpp"
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
		std::cout << "boom" << "\n";
		for (Component::Component *c : _components)
		{
			delete c;
		}
		_components.clear();
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
    void    GameObject::renderUI(struct nk_context *ctx) {}

	void     GameObject::destroy(Component::Component *comp)
	{
		for (int i = 0; i <_components.size(); i++)
		{
			if (_components[i] == comp)
			{
				_components.erase(_components.begin() + i);
				return ;
			}
		}
	}

	void    GameObject::destroy(GameObject *go)
    {
        _scene.destroy(go);
    }

	void    GameObject::componentStart(void)
	{
		// for (Component::Component *c : _components)
		// {
		// 	if (Component::IStart *u = dynamic_cast<Component::IStart*>(c))
		// 		u->start();
		// }
		for (Component::IStart *s : _toStart)
			s->start();
		_toStart.clear();
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
			else if (Component::IRenderAlpha *r = dynamic_cast<Component::IRenderAlpha*>(c))
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
	void    GameObject::componentRenderAlpha(void)
	{
		for (Component::Component *c : _components)
		{
			if (Component::IRenderAlpha *r = dynamic_cast<Component::IRenderAlpha*>(c))
				r->render();
		}
	}

	void    GameObject::componentPhysicUpdate(void)
	{
		for (Component::Component *c : _components)
		{
			if (auto *p = dynamic_cast<Component::RigidBody2D*>(c))
				p->physicUpdate();
		}
		for (Component::Component *c : _components)
		{
			if (auto *p = dynamic_cast<Component::ACollider*>(c))
				p->physicUpdate();
		}
	}

	void    GameObject::componentRenderUI(struct nk_context *ctx)
	{
		for (Component::Component *c : _components)
		{
			if (Component::IUI *r = dynamic_cast<Component::IUI*>(c))
				r->renderUI(ctx);
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

	GameObject * GameObject::Deserialize(const nlohmann::json & j, AScene &scene)
    {
		int id = j.at("id");
		auto go = new GameObject(id, scene);
		go->name = j.at("name");
		go->transform = Transform::Deserialize(j.at("transform"));
		auto components = j.at("components");
        for (nlohmann::json::iterator it = components.begin(); it != components.end(); ++it) {
			auto comp = Component::Component::Deserialize(it.value(), go);
			go->_components.push_back(comp);
		}
		return go;
    }
}
