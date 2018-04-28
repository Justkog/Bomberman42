#include "Core/Component/Component.hpp"
#include "Core/Json/Json.hpp"

namespace BeerEngine
{
	namespace Component
	{
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