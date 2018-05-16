#ifndef BE_CORE_COMPONENT_CIRCLECOLLIDER_HPP
#define BE_CORE_COMPONENT_CIRCLECOLLIDER_HPP 1
/*!
 * \file CircleCollider.hpp
 * \brief Component de collision en cercle
 * \author qhonore
 */
#include "Core/Core.hpp"
#include "ACollider.hpp"

namespace BeerEngine
{
	namespace Component
	{
		/*! \class BoxCollider2D
		* \brief classe heritante du systeme de base des collision pour effectuer des collisions par des cercles
		*/
		class CircleCollider : public ACollider
		{
		protected:
			bool lineCollision(glm::vec2 A, glm::vec2 B, glm::vec2 C);
			bool segmentCollision(glm::vec2 A, glm::vec2 B, glm::vec2 C);

		public:
			CircleCollider(GameObject *gameObject);
			virtual ~CircleCollider();
			bool checkCollision(ACollider *other);

			bool contain(glm::vec2 other);
			bool intersect(glm::vec2 origin, glm::vec2 dir);
			bool intersect(glm::vec2 origin, glm::vec2 dir, glm::vec2 &outPosition);

			bool collide_AABB2D(CircleCollider *other);
			bool collide_AABB2D(BoxCollider2D *other);

			void response_AABB2D(CircleCollider *other, glm::vec2 &thisPos, glm::vec2 &otherPos);

			float	_radius;

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif