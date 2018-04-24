#include "Core/Component/BoxCollider2D.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		BoxCollider2D::BoxCollider2D(GameObject *gameObject) :
			ACollider(gameObject)
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
	}
}