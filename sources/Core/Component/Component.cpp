#include "Core/Component/Component.hpp"
#include "Core/Json/Json.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		add_component_type Component::createAddMap()
		{
			add_component_type typeToAddComponent;
			typeToAddComponent["Component"] = &Component::addComponent<Component>;
			return typeToAddComponent;
		}

		add_component_type Component::typeToAddComponent = Component::createAddMap();

		Component::Component(GameObject *gameObject) :
			_gameObject(gameObject)
		{

		}

		nlohmann::json	Component::serialize()
		{
			return nlohmann::json {
				{"componentClass", "Component"}
			};
		}

		void Component::deserialize(const nlohmann::json & j)
		{

		}

		Component * Component::Deserialize(const nlohmann::json & j, GameObject *go)
		{
			// std::cout << "deserialize component : " << j << "\n";
			std::string type = j.at("componentClass");
			// std::cout << "after" << "\n";
			auto mapIt = Component::Component::typeToAddComponent.find(type);
			if(mapIt != Component::Component::typeToAddComponent.end())
			{
				auto component = Component::Component::typeToAddComponent[type](go);
				component->deserialize(j);
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