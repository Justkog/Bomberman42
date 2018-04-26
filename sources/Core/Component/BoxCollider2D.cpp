#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/Component/ITriggerStay.hpp"
#include "Core/Component/ITriggerEnter.hpp"
#include "Core/Component/ITriggerExit.hpp"
#include "Core/GameObject.hpp"

#include <vector>

namespace BeerEngine
{
	namespace Component
	{
		BoxCollider2D::BoxCollider2D(GameObject *gameObject) :
			ACollider(gameObject),
			_size(glm::vec2(gameObject->transform.scale.x, gameObject->transform.scale.z))
		{}

		bool BoxCollider2D::checkCollision(ACollider *other)
		{
			if (other->collide_AABB2D(this))
				return true;
			else
				return false;
		}

		bool BoxCollider2D::collide_AABB2D(BoxCollider2D *other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 otherPos(other->_transform.position.x + other->_offset.x, other->_transform.position.z + other->_offset.y);

			if (thisPos.x - _size.x / 2 > otherPos.x + other->_size.x / 2
			|| thisPos.x + _size.x / 2 < otherPos.x - other->_size.x / 2
			|| thisPos.y - _size.y / 2 > otherPos.y + other->_size.y / 2
			|| thisPos.y + _size.y / 2 < otherPos.y - other->_size.y / 2)
				return (false);
			
			return (true);
		}

		bool BoxCollider2D::collide_AABB2D(CircleCollider *other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 otherPos(other->_transform.position.x + other->_offset.x, other->_transform.position.z + other->_offset.y);
			glm::vec2 nearest(glm::clamp(otherPos.x, thisPos.x - _size.x / 2, thisPos.x + _size.x / 2), glm::clamp(otherPos.y, thisPos.y - _size.y / 2, thisPos.y + _size.y / 2));

			if (glm::distance2(nearest, otherPos) < other->_radius * other->_radius)
				return (true);
			return (false);
		}
	}
}