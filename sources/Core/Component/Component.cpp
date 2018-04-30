#include "Core/Component/Component.hpp"
#include "Core/Json/Json.hpp"

namespace BeerEngine
{
	namespace Component
	{
		// void Component::RegisterComponentType()
		// {
		// 	Component::typeToComponent["Component"] = &Component::createInstance<Component>;
		// }

		component_type Component::create_map()
		{
			component_type typeToComponent;
			typeToComponent["Component"] = &Component::createInstance<Component>;
			return typeToComponent;
		}

		component_type Component::typeToComponent = Component::create_map();

		template<typename T>
		Component * Component::createInstance(GameObject *gameObject)
		{ 
			return new T(gameObject); 
		}


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
	}
}