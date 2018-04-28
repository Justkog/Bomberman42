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
			bool 	checkCollision(ACollider *other);


			bool collide_AABB2D(BoxCollider2D *other);
			bool collide_AABB2D(CircleCollider *other);

			void response_AABB2D(BoxCollider2D *other, glm::vec2 &thisPos, glm::vec2 &otherPos);
			void response_AABB2D(CircleCollider *other, glm::vec2 &nearest, glm::vec2 &otherPos);

			virtual nlohmann::json	serialize()
			{
				return {
					{"componentClass", typeid(BoxCollider2D).name()},
					{"size", _size},
				};
			}

			glm::vec2	_size;
		};
	}
}

#endif