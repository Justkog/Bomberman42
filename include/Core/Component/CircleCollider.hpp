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
			virtual ~CircleCollider();
			bool 	checkCollision(ACollider *other);

			bool collide_AABB2D(CircleCollider *other);
			bool collide_AABB2D(BoxCollider2D *other);

			void response_AABB2D(CircleCollider *other, glm::vec2 &thisPos, glm::vec2 &otherPos);

			float	_radius;

			virtual nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif