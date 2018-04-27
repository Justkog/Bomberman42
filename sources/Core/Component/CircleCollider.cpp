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
				return (true);
			else
				return (false);
		}

		bool CircleCollider::collide_AABB2D(CircleCollider *other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 otherPos(other->_transform.position.x + other->_offset.x, other->_transform.position.z + other->_offset.y);

			if (glm::distance2(thisPos, otherPos) < (_radius + other->_radius) * (_radius + other->_radius))
			{
				response_AABB2D(other, thisPos, otherPos);
				return (true);
			}
			return (false);
		}

		bool CircleCollider::collide_AABB2D(BoxCollider2D *other)
		{
			return (other->collide_AABB2D(this));
		}

		void CircleCollider::response_AABB2D(CircleCollider *other, glm::vec2 &thisPos, glm::vec2 &otherPos)
		{
			float overlap = (_radius + other->_radius) - glm::distance(thisPos, otherPos);
			glm::vec3 dir(thisPos.x - otherPos.x, 0, thisPos.y - otherPos.y);
			dir = glm::normalize(dir);

			if (other->_kinematic && !_kinematic)
				_transform.translate(dir * overlap);
			else if (!other->_kinematic && _kinematic)
				other->_transform.translate(-dir * overlap);
			else if (!other->_kinematic && !_kinematic)
			{
				_transform.translate(dir * (overlap / 2));
				other->_transform.translate(-dir * (overlap / 2));
			}
		}
	}
}