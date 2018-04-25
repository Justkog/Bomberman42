#ifndef BE_CORE_COMPONENT_ACOLLIDER_HPP
#define BE_CORE_COMPONENT_ACOLLIDER_HPP 1

#include "../BeerEngine.hpp"
#include "Component.hpp"
#include "IUpdate.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class BoxCollider2D;
		class CircleCollider;

		class ACollider : public Component
		{
		protected:

		public:
			ACollider(GameObject *gameObject);
			virtual void    physicUpdate(void) = 0;

			virtual bool collide_AABB2D(CircleCollider *other) = 0;
			virtual bool collide_AABB2D(BoxCollider2D *other) = 0;

			static std::vector<ACollider*> _colliders;
			glm::vec2	_offset;
			Transform	&_transform;
			bool		_collide;
		};
	}
}

#endif