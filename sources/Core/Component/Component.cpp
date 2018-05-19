#include "Core/Component/Component.hpp"
#include "Core/Json/Json.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		Component::Component()
		{}

		Component::Component(const Component &val)
		{
			*this = val;
		}
		
		Component &Component::operator=(const Component &val)
		{
			if (this != &val)
			{
				_gameObject = val._gameObject;
				_isActive = val._isActive;
			}
			return (*this);
		}

		add_component_type Component::createAddMap()
		{
			add_component_type typeToAddComponent;
			typeToAddComponent["Component"] = &Component::addComponent<Component>;
			return typeToAddComponent;
		}

		add_component_type Component::typeToAddComponent = Component::createAddMap();

		Component::Component(GameObject *gameObject) :
			_gameObject(gameObject), _isActive(true)
		{
			// setActive(true);
		}

		void	Component::setActive(bool state)
		{
			if (state)
				_gameObject->enableComponent(this);
			else if (!state)
				_gameObject->disableComponent(this);
		}

		nlohmann::json	Component::serialize()
		{
			auto j = JsonSerializable::serialize();
			j.merge_patch({
				{"componentClass", "Component"},
				{"enabled", _isActive},
			});
			return j;
		}

		void Component::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			this->JsonSerializable::deserialize(j, loader);
			this->setActive(j.at("enabled"));
		}

		Component * Component::Deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader, GameObject *go)
		{
			// std::cout << "deserialize component : " << j << "\n";
			std::string type = j.at("componentClass");
			auto mapIt = Component::Component::typeToAddComponent.find(type);
			if(mapIt != Component::Component::typeToAddComponent.end())
			{
				auto component = Component::Component::typeToAddComponent[type](go);
				component->deserialize(j, loader);
				// std::cout << "deserialize component done" << "\n";
				return component;
			}
			// std::cout << "deserialize component done got none" << "\n";
			return NULL;
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