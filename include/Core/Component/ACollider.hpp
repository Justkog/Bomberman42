#ifndef BE_CORE_COMPONENT_ACOLLIDER_HPP
#define BE_CORE_COMPONENT_ACOLLIDER_HPP 1

#include "../BeerEngine.hpp"
#include "Component.hpp"
#include "IUpdate.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class ACollider : public Component
		{
		protected:

		public:
			ACollider(GameObject *gameObject);
			virtual void    physicUpdate(void);

			static std::vector<ACollider*> _colliders;
			glm::vec2	_offset;
			Transform	&_transform;
		};
	}
}

#endif