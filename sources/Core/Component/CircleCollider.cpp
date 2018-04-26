#include "Core/Component/CircleCollider.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		CircleCollider::CircleCollider(GameObject *gameObject) :
			ACollider(gameObject),
			_radius((gameObject->transform.scale.x + gameObject->transform.scale.z) / 4)
		{}

		bool CircleCollider::checkCollision(ACollider *other)
		{
			if (other->collide_AABB2D(this))
				return true;
			else
				return false;
		}

		bool CircleCollider::collide_AABB2D(CircleCollider *other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 otherPos(other->_transform.position.x + other->_offset.x, other->_transform.position.z + other->_offset.y);

			if (glm::distance2(thisPos, otherPos) < (_radius + other->_radius) * (_radius + other->_radius))
				return (true);
			return (false);
		}

		bool CircleCollider::collide_AABB2D(BoxCollider2D *other)
		{
			return other->collide_AABB2D(this);
		}
	}
}