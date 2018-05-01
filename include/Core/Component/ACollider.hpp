#ifndef BE_CORE_COMPONENT_ACOLLIDER_HPP
#define BE_CORE_COMPONENT_ACOLLIDER_HPP 1

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class ACollider : public Component, public IStart
		{
		protected:

		public:
			ACollider(GameObject *gameObject);
			virtual ~ACollider();
			void    start(void);

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

			bool		isKinematic(void);

			void		response(ACollider *other, glm::vec3 move);

			static std::vector<ACollider*> _colliders;
			std::vector<ACollider*> _currentCollisions;
			Transform	&_transform;
			glm::vec2	_offset;
			bool		_isTrigger;
			// bool		_kinematic;
			RigidBody2D *rb2d;
		};
	}
}

#endif