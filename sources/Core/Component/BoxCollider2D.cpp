#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		BoxCollider2D::BoxCollider2D(GameObject *gameObject) :
			ACollider(gameObject),
			_size(glm::vec2(1, 1))
		{}

		void    		BoxCollider2D::fixedUpdate(void)
		{
		}

		void    		BoxCollider2D::update(void)
		{
		}

		bool BoxCollider2D::collide_AABB2D(BoxCollider2D &other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.y + _offset.y);
			glm::vec2 otherPos(other._transform.position.x + other._offset.x, other._transform.position.y + other._offset.y);

			if (thisPos.x < otherPos.x + other._size.x
			&& thisPos.x + _size.x > otherPos.x
			&& thisPos.y < otherPos.y + other._size.y
			&& thisPos.y + _size.y > otherPos.y)
				return (true);
			return (false);
		}

		bool BoxCollider2D::collide_AABB2D(CircleCollider &other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.y + _offset.y);
			glm::vec2 otherPos(other._transform.position.x + other._offset.x, other._transform.position.y + other._offset.y);
			glm::vec2 nearest(glm::clamp(otherPos.x, thisPos.x, thisPos.x + _size.x), glm::clamp(otherPos.y, thisPos.y, thisPos.y + _size.y));

			if (glm::distance2(nearest, otherPos) < other._radius * other._radius)
				return (true);
			return (false);
		}
	}
}