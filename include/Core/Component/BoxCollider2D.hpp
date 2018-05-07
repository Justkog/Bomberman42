#ifndef BE_CORE_COMPONENT_BOXCOLLIDER2D_HPP
#define BE_CORE_COMPONENT_BOXCOLLIDER2D_HPP 1

#include "Core/Core.hpp"
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
			virtual ~BoxCollider2D();
			bool checkCollision(ACollider *other);

			bool contain(glm::vec2 other);
			bool intersect(glm::vec2 origin, glm::vec2 dir);
			bool intersect(glm::vec2 origin, glm::vec2 dir, glm::vec2 &outPosition);

			bool collide_AABB2D(BoxCollider2D *other);
			bool collide_AABB2D(CircleCollider *other);

			void response_AABB2D(BoxCollider2D *other, glm::vec2 &thisPos, glm::vec2 &otherPos);
			void response_AABB2D(CircleCollider *other, glm::vec2 &nearest, glm::vec2 &otherPos);

			glm::vec2	_size;

			virtual nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif