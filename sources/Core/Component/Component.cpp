#include "Core/Component/Component.hpp"
#include "Core/Json/Json.hpp"

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
			std::string type = j.at("componentClass");
			auto mapIt = Component::Component::typeToComponent.find(type);
			if(mapIt != Component::Component::typeToComponent.end())
			{
				auto component = Component::Component::typeToComponent[type](go);
				component->deserialize(j);
				return component;
			}
			return NULL;
		}
	}
}