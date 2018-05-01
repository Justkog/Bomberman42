#include "Core/Component/Component.hpp"
#include "Core/Json/Json.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		component_type Component::create_map()
		{
			component_type typeToComponent;
			typeToComponent["Component"] = &Component::createInstance<Component>;
			return typeToComponent;
		}

		component_type Component::typeToComponent = Component::create_map();

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
			std::cout << "deserialize component : " << j << "\n";
			std::string type = j.at("componentClass");
			std::cout << "after" << "\n";
			auto mapIt = Component::Component::typeToComponent.find(type);
			if(mapIt != Component::Component::typeToComponent.end())
			{
				auto component = Component::Component::typeToComponent[type](go);
				component->deserialize(j);
				std::cout << "deserialize component done" << "\n";
				return component;
			}
			std::cout << "deserialize component done got none" << "\n";
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