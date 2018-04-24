#ifndef BE_CORE_COMPONENT_BOXCOLLIDER2D_HPP
#define BE_CORE_COMPONENT_BOXCOLLIDER2D_HPP 1

#include "ACollider.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class CircleCollider;

		class BoxCollider2D : public ACollider
		{
		protected:

		public:
			BoxCollider2D(GameObject *gameObject);
			virtual void    physicUpdate(void);

			bool collide_AABB2D(BoxCollider2D *other);
			bool collide_AABB2D(CircleCollider *other);

			glm::vec2	_size;
		};
	}
}

#endif