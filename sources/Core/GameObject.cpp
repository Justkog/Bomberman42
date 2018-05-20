#include <Game/Level1.hpp>
#include "Core/GameObject.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IRender.hpp"
#include "Core/Component/IRenderAlpha.hpp"
#include "Core/Component/IRenderForward.hpp"
#include "Core/Component/IRenderShadow.hpp"
#include "Core/Component/IUI.hpp"
#include "Core/Component/IStartUI.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IEnable.hpp"
#include "Core/Component/IDisable.hpp"
#include "Core/Component/ACollider.hpp"
#include "Core/Component/IOnDestroy.hpp"
#include "Core/Transform.hpp"
#include "Core/Component/RigidBody2D.hpp"
#include "Core/Json/Json.hpp"
#include "Core/AScene.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Core/Time.hpp"

namespace BeerEngine
{
    GameObject::GameObject(int uniqueID, AScene &scene) :
		_uniqueID(uniqueID),
		_scene(scene)
	{
		immortalTimer = 0.0f;
	}

	GameObject::GameObject() :
		_scene(Level1::instance)
	{}

	GameObject::GameObject(const GameObject &val) :
		_scene(val._scene)
	{
		*this = val;
	}

	GameObject &GameObject::operator=(const GameObject &val)
	{
		if (this != &val)
		{
			for (std::size_t i = 0; i < val._components.size(); i++)
				_components.push_back(val._components[i]);
			for (std::size_t i = 0; i < val._toStart.size(); i++)
				_toStart.push_back(val._toStart[i]);
			for (std::size_t i = 0; i < val._toStartUI.size(); i++)
				_toStartUI.push_back(val._toStartUI[i]);
			for (std::size_t i = 0; i < val._toEnable.size(); i++)
				_toEnable.push_back(val._toEnable[i]);
			for (std::size_t i = 0; i < val._toDisable.size(); i++)
				_toDisable.push_back(val._toDisable[i]);
			for (std::size_t i = 0; i < val._toDestroy.size(); i++)
				_toDestroy.push_back(val._toDestroy[i]);

			_uniqueID = val._uniqueID;
			_scene = val._scene;
			transform = val.transform;
			name = val.name;
			immortalTimer = val.immortalTimer;

		}
		return (*this);
	}

	GameObject::~GameObject(void)
	{
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

	bool	GameObject::isImmortal(void)
	{
		return (immortalTimer > 0.0f);
	}

	std::vector<Component::Component *> GameObject::GetComponents(void)
	{
		return _components;
	}

	void	GameObject::start(void) {}
	void    GameObject::fixedUpdate(void) {}
	void    GameObject::update(void)
	{
		if (immortalTimer > 0.0f)
			immortalTimer -= Time::GetDeltaTime();
	}
	void    GameObject::renderUpdate(void) {}
	void    GameObject::render(void) {}
    void    GameObject::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts) { (void) ctx;  (void) fonts; }
    void    GameObject::renderUI(struct nk_context *ctx) { (void) ctx; }

	void     GameObject::destroy(Component::Component *comp)
	{
		if(std::find(_toDestroy.begin(), _toDestroy.end(), comp) == _toDestroy.end())
			_toDestroy.push_back(comp);
	}
	void    GameObject::destroyComponent(void)
	{
		for (Component::Component *comp : _toDestroy)
		{
			if (auto *d = dynamic_cast<Component::IOnDestroy*>(comp))
					d->onDestroy();
		}
		for (Component::Component *comp : _toDestroy)
		{
			for (std::size_t i = 0; i <_components.size(); i++)
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

	void GameObject::enableComponent(Component::Component *comp)
	{
		// std::cout << "attempting to enable" << std::endl;
		
		auto it = std::find(_toDisable.begin(), _toDisable.end(), comp);
		if (it != _toDisable.end())
		{
			// std::cout << "comp was about to be disabled" << std::endl;
			comp->_isActive = true;
			_toDisable.erase(it);
			return;
		}
		else if (comp->_isActive)
			return;
		// std::cout << "added to enable" << std::endl;
		_toEnable.push_back(comp);
	}

	void GameObject::disableComponent(Component::Component *comp)
	{
		// std::cout << "attempting to disable" << std::endl;
		auto it = std::find(_toEnable.begin(), _toEnable.end(), comp);
		if (it != _toEnable.end())
		{
			std::cout << "comp was about to be enabled" << std::endl;
			comp->_isActive = false;
			_toEnable.erase(it);
			return;
		}
		else if (!comp->_isActive)
		{
			// std::cout << "component is already disabled" << std::endl;
			return;
		}
		// std::cout << "added to disable" << std::endl;
		_toDisable.push_back(comp);
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

	void    GameObject::componentEnable(void)
	{
        // std::cout << "DEBUG: GameObject::componentEnable" << std::endl;
		for (Component::Component *c : _toEnable)
		{
			c->_isActive = true;
			if (Component::IEnable *u = dynamic_cast<Component::IEnable*>(c))
				u->enable();
		}
		_toEnable.clear();
	}

	void    GameObject::componentDisable(void)
	{
        // std::cout << "DEBUG: GameObject::componentDisable" << std::endl;
		for (Component::Component *c : _toDisable)
		{
			c->_isActive = false;
			if (Component::IDisable *u = dynamic_cast<Component::IDisable*>(c))
				u->disable();
		}
		_toDisable.clear();
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
			if (Component::IRenderForward *r = dynamic_cast<Component::IRenderForward*>(c))
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

	void    GameObject::componentRenderForward(Graphics::ALight &light)
	{
        // std::cout << "DEBUG: GameObject::componentRender" << std::endl;
		for (Component::Component *c : _components)
		{
			if (!c->_isActive)
				continue;
			if (Component::IRenderForward *r = dynamic_cast<Component::IRenderForward*>(c))
				r->render(light);
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

	void    GameObject::componentRenderShadows(void)
	{
		for (Component::Component *c : _components)
		{
			if (!c->_isActive)
				continue;
			if (Component::IRenderShadow *r = dynamic_cast<Component::IRenderShadow*>(c))
			{
				r->renderShadow();
			}
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

	void    GameObject::componentOnDestroy(void)
	{
		for (Component::Component *c : _components)
		{
			if (auto *d = dynamic_cast<Component::IOnDestroy*>(c))
				d->onDestroy();
		}
	}

	nlohmann::json	GameObject::serialize()
	{
		auto j = JsonSerializable::serialize();
		j.merge_patch({
            {"id", this->_uniqueID},
            {"name", this->name},
            {"transform", JsonSerializable::toSerializable(this->transform)},
            {"components", JsonSerializable::toSerializables<BeerEngine::Component::Component>(this->GetComponents())}
		});
		return j;
	}

	void GameObject::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
    {
		this->JsonSerializable::deserialize(j, loader);
		this->_uniqueID = j.at("id");
		this->name = j.at("name");
		this->transform = Transform::Deserialize(j.at("transform"), loader);
		auto components = j.at("components");
        for (nlohmann::json::iterator it = components.begin(); it != components.end(); ++it) {
			Component::Component::Deserialize(it.value(), loader, this);
		}
    }

	GameObject * GameObject::Deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader, AScene &scene)
    {
		// int id = j.at("id");
		auto go = scene.instantiate<GameObject>();
		// auto go = new GameObject(id, scene);
		go->deserialize(j, loader);
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
        // std::cout << "deserializing GO " << filePath << "\n";
        auto j = nlohmann::json::parse(content);
		// std::cout << "json loaded" << "\n";
		BeerEngine::JsonLoader loader;
        this->deserialize(j, loader);
		loader.executeCallBacks();
    }
}
