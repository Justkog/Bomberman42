#ifndef BE_CORE_COMPONENT_BOXCOLLIDER2D_HPP
#define BE_CORE_COMPONENT_BOXCOLLIDER2D_HPP 1
/*!
 * \file BoxCollider2D.hpp
 * \brief Component de collision en rectangle
 * \author qhonore, jblondea
 */
#include "Core/Core.hpp"
#include "ACollider.hpp"

namespace BeerEngine
{
	namespace Component
	{
		/*! \class BoxCollider2D
		* \brief classe heritante du systeme de base des collision pour effectuer des collisions AABB en 2D (Axis-Aligned Bounding Box)
		*/
		class BoxCollider2D : public ACollider
		{
		protected:

		public:
			BoxCollider2D();
			BoxCollider2D(const BoxCollider2D &val);
			BoxCollider2D &operator=(const BoxCollider2D &val);

			BoxCollider2D(GameObject *gameObject);
			virtual ~BoxCollider2D();
			bool checkCollision(ACollider *other, bool response = true);

			bool contain(glm::vec2 other);
			bool intersect(glm::vec2 origin, glm::vec2 dir);
			bool intersect(glm::vec2 origin, glm::vec2 dir, glm::vec2 &outPosition);

			bool collide_AABB2D(BoxCollider2D *other, bool response = true);
			bool collide_AABB2D(CircleCollider *other, bool response = true);

			void response_AABB2D(BoxCollider2D *other, glm::vec2 &thisPos, glm::vec2 &otherPos);
			void response_AABB2D(CircleCollider *other, glm::vec2 &nearest, glm::vec2 &otherPos);

			glm::vec2	_size;

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif