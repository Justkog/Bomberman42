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
			virtual void    physicUpdate(void);
			virtual bool 	checkCollision(ACollider *other) = 0;

			virtual bool collide_AABB2D(CircleCollider *other) = 0;
			virtual bool collide_AABB2D(BoxCollider2D *other) = 0;

			virtual void triggerStay(ACollider *other);
			virtual void triggerEnter(ACollider *other);
			virtual void triggerExit(ACollider *other);

			virtual void colliderStay(ACollider *other);
			virtual void colliderEnter(ACollider *other);
			virtual void colliderExit(ACollider *other);

			static std::vector<ACollider*> _colliders;
			std::vector<ACollider*> _currentCollisions;
			int			_id;
			glm::vec2	_offset;
			Transform	&_transform;
			bool		_collide;
			bool		_isTrigger;
		};
	}
}

#endif