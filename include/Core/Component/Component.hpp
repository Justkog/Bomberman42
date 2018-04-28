#ifndef BE_CORE_COMPONENT_HPP
#define BE_CORE_COMPONENT_HPP 1

#include "Core/Core.hpp"

namespace BeerEngine
{
	class GameObject;
}

namespace BeerEngine
{
	namespace Component
	{
		class Component
		{
		protected:
		public:
			Component(GameObject *gameObject);
			virtual ~Component(void) {}

			GameObject		*_gameObject;
			virtual nlohmann::json	serialize();
		};
	}
}

#endif