#ifndef BE_CORE_COMPONENT_CIRCLECOLLIDER_HPP
#define BE_CORE_COMPONENT_CIRCLECOLLIDER_HPP 1

#include "ACollider.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class BoxCollider2D;

		class CircleCollider : public ACollider
		{
		protected:

		public:
			CircleCollider(GameObject *gameObject);
			virtual void    physicUpdate(void);

			bool collide_AABB2D(CircleCollider *other);
			bool collide_AABB2D(BoxCollider2D *other);

			float	_radius;
		};
	}
}

#endif