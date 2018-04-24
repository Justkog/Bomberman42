#include "Core/Component/CircleCollider.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		CircleCollider::CircleCollider(GameObject *gameObject) :
			ACollider(gameObject),
			_radius(1)
		{}

		void    CircleCollider::physicUpdate(void)
		{
			int pos = std::find(_colliders.begin(), _colliders.end(), this) - _colliders.begin();

			if (pos < _colliders.size())
				return;

			for (; pos < _colliders.size() - 1; ++pos)
			{
				auto pouet = _colliders[pos + 1];
				if (collide_AABB2D(dynamic_cast<BoxCollider2D*>(pouet)))
				{
					// auto collisionTriggers = _colliders[pos + 1]->_gameObject->GetComponents<ICollision>();
					// for (auto comp: collisionTriggers)
					// {
					// 	// call onCollisionStay
					// }
				}
			}
		}

		bool CircleCollider::collide_AABB2D(CircleCollider *other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 otherPos(other->_transform.position.x + other->_offset.x, other->_transform.position.z + other->_offset.y);

			if (glm::distance2(thisPos, otherPos) < _radius * _radius + other->_radius * other->_radius)
				return (true);
			return (false);
		}

		bool CircleCollider::collide_AABB2D(BoxCollider2D *other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 otherPos(other->_transform.position.x + other->_offset.x, other->_transform.position.z + other->_offset.y);
			glm::vec2 nearest(glm::clamp(thisPos.x, otherPos.x, otherPos.x + other->_size.x), glm::clamp(thisPos.y, otherPos.y, otherPos.y + other->_size.y));

			if (glm::distance2(nearest, thisPos) < _radius * _radius)
				return (true);
			return (false);
		}
	}
}