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
			Maths::Vector2f thisPos(_transform.position.getX() + _offset.getX(), _transform.position.getY() + _offset.getY());
			Maths::Vector2f otherPos(other._transform.position.getX() + other._offset.getX(), other._transform.position.getY() + other._offset.getY());

			if (thisPos.getX() < otherPos.getX() + other._size.getX()
			&& thisPos.getX() + _size.getX() > otherPos.getX()
			&& thisPos.getY() < otherPos.getY() + other._size.getY()
			&& thisPos.getY() + _size.getY() > otherPos.getY())
				return (true);
			return (false);
		}
	}
}