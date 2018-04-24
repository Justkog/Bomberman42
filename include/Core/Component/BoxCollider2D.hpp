#ifndef BE_CORE_COMPONENT_BOXCOLLIDER2D_HPP
#define BE_CORE_COMPONENT_BOXCOLLIDER2D_HPP 1

#include "ACollider.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class BoxCollider2D : public ACollider
		{
		protected:

		public:
			BoxCollider2D(GameObject *gameObject);
			virtual void    fixedUpdate(void);
			virtual void    update(void);

			bool collide_AABB2D(BoxCollider2D &collider);
		};
	}
}

#endif