#ifndef BE_CORE_COMPONENT_CIRCLECOLLIDER_HPP
#define BE_CORE_COMPONENT_CIRCLECOLLIDER_HPP 1

#include "Core/Core.hpp"
#include "ACollider.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class CircleCollider : public ACollider
		{
		protected:

		public:
			CircleCollider(GameObject *gameObject);
			bool 	checkCollision(ACollider *other);

			bool collide_AABB2D(CircleCollider *other);
			bool collide_AABB2D(BoxCollider2D *other);

			void response_AABB2D(CircleCollider *other, glm::vec2 &thisPos, glm::vec2 &otherPos);
			virtual nlohmann::json	serialize();


			float	_radius;
		};
	}
}

#endif