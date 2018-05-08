#include "Core/GameObject.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IRender.hpp"
#include "Core/Component/IRenderAlpha.hpp"
#include "Core/Component/IUI.hpp"
#include "Core/Component/IStartUI.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/ACollider.hpp"
#include "Core/Transform.hpp"
#include "Core/Component/RigidBody2D.hpp"
#include "Core/Json/Json.hpp"
#include "Core/AScene.hpp"
#include "Core/IO/FileUtils.hpp"

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
    void    GameObject::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts) {}
    void    GameObject::renderUI(struct nk_context *ctx) {}

	void     GameObject::destroy(Component::Component *comp)
	{
		if(std::find(_toDestroy.begin(), _toDestroy.end(), comp) == _toDestroy.end())
			_toDestroy.push_back(comp);
	}
	void    GameObject::destroyComponent(void)
	{
		for (Component::Component *comp : _toDestroy)
		{
			for (int i = 0; i <_components.size(); i++)
			{
				if (_components[i] == comp)
				{
					_components.erase(_components.begin() + i);
					break;
				}
			}
			delete comp;
		}
        _toDestroy.clear();
	}

	void    GameObject::destroy(GameObject *go)
    {
        _scene.destroy(go);
    }

	void    GameObject::componentStart(void)
	{
        // std::cout << "DEBUG: GameObject::componentStart" << std::endl;
		for (Component::Component *c : _toStart)
		{
			if (Component::IStart *u = dynamic_cast<Component::IStart*>(c))
				u->start();
			// _components.push_back(c);
		}
		_toStart.clear();
	}

	void    GameObject::componentFixedUpdate(void)
	{
        // std::cout << "DEBUG: GameObject::componentFixedUpdate" << std::endl;
		for (Component::Component *c : _components)
		{
			if (!c->_isActive)
				continue;
			if (Component::IUpdate *u = dynamic_cast<Component::IUpdate*>(c))
				u->fixedUpdate();
		}
	}

	void    GameObject::componentUpdate(void)
	{
        // std::cout << "DEBUG: GameObject::componentUpdate" << std::endl;
		for (Component::Component *c : _components)
		{
			if (!c->_isActive)
				continue;
			if (Component::IUpdate *u = dynamic_cast<Component::IUpdate*>(c))
				u->update();
		}
	}

	void    GameObject::componentRenderUpdate(void)
	{
        // std::cout << "DEBUG: GameObject::componentRenderUpdate" << std::endl;
		for (Component::Component *c : _components)
		{
			if (!c->_isActive)
				continue;
			if (Component::IRender *r = dynamic_cast<Component::IRender*>(c))
				r->renderUpdate();
			if (Component::IRenderAlpha *r = dynamic_cast<Component::IRenderAlpha*>(c))
				r->renderAlphaUpdate();
		}
	}

	void    GameObject::componentRender(void)
	{
        // std::cout << "DEBUG: GameObject::componentRender" << std::endl;
		for (Component::Component *c : _components)
		{
			if (!c->_isActive)
				continue;
			if (Component::IRender *r = dynamic_cast<Component::IRender*>(c))
				r->render();
		}
	}
	void    GameObject::componentRenderAlpha(void)
	{
        // std::cout << "DEBUG: GameObject::componentRenderAlpha" << std::endl;
		for (Component::Component *c : _components)
		{
			if (!c->_isActive)
				continue;
			if (Component::IRenderAlpha *r = dynamic_cast<Component::IRenderAlpha*>(c))
				r->renderAlpha();
		}
	}

	void    GameObject::componentPhysicUpdate(void)
	{
        // std::cout << "DEBUG: GameObject::componentPhysicUpdate" << std::endl;
		for (Component::Component *c : _components)
		{
			if (!c->_isActive)
				continue;
			if (auto *p = dynamic_cast<Component::RigidBody2D*>(c))
				p->physicUpdate();
		}
		for (Component::Component *c : _components)
		{
			if (!c->_isActive)
				continue;
			if (auto *p = dynamic_cast<Component::ACollider*>(c))
				p->physicUpdate();
		}
	}

	void    GameObject::componentRenderUI(struct nk_context *ctx)
	{
        // std::cout << "DEBUG: GameObject::componentRenderUI" << std::endl;
		for (Component::Component *c : _components)
		{
			if (!c->_isActive)
				continue;
			if (Component::IUI *r = dynamic_cast<Component::IUI*>(c))
				r->renderUI(ctx);
		}
	}

	void    GameObject::componentStartUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
	{
		// std::cout << "DEBUG: GameObject::componentStart" << std::endl;
		for (Component::Component *c : _toStartUI)
		{
			if (auto u = dynamic_cast<Component::IStartUI*>(c))
				u->startUI(ctx, fonts);
			// _components.push_back(c);
		}
		_toStartUI.clear();
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

	void GameObject::deserialize(const nlohmann::json & j)
    {
		this->name = j.at("name");
		this->transform = Transform::Deserialize(j.at("transform"));
		auto components = j.at("components");
        for (nlohmann::json::iterator it = components.begin(); it != components.end(); ++it) {
			auto comp = Component::Component::Deserialize(it.value(), this);
		}
    }

	GameObject * GameObject::Deserialize(const nlohmann::json & j, AScene &scene)
    {
		int id = j.at("id");
		auto go = new GameObject(id, scene);
		go->deserialize(j);
		return go;
    }

	void    GameObject::save(std::string filePath) {
        nlohmann::json j = dynamic_cast<JsonSerializable *>(this);
        std::string content = j.dump(4);
        BeerEngine::IO::FileUtils::WriteFile(filePath, content);
        // std::cout << content << std::endl;
    }

    void    GameObject::load(std::string filePath) {
        std::string content = BeerEngine::IO::FileUtils::LoadFile(filePath);
        // std::cout << "deserializing " << filePath << "\n";
        auto j = nlohmann::json::parse(content);
		// std::cout << "json loaded" << "\n";
        this->deserialize(j);
    }
}
