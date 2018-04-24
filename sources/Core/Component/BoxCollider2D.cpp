#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		BoxCollider2D::BoxCollider2D(GameObject *gameObject) :
			ACollider(gameObject),
			_size(glm::vec2(gameObject->transform.scale.x, gameObject->transform.scale.z))
		{}

		void    BoxCollider2D::physicUpdate(void)
		{
			int pos = std::find(_colliders.begin(), _colliders.end(), this) - _colliders.begin();

			if (pos < _colliders.size())
				return;

			for (; pos < _colliders.size() - 1; ++pos)
			{
				auto pouet = _colliders[pos + 1];
				if (pouet->collide_AABB2D(this))
				{
					// auto collisionTriggers = _colliders[pos + 1]->_gameObject->GetComponents<ICollision>();
					// for (auto comp: collisionTriggers)
					// {
					// 	// call onCollisionStay
					// }
				}
			}
		}

		bool BoxCollider2D::collide_AABB2D(BoxCollider2D *other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 otherPos(other->_transform.position.x + other->_offset.x, other->_transform.position.z + other->_offset.y);

			if (thisPos.x < otherPos.x + other->_size.x
			&& thisPos.x + _size.x > otherPos.x
			&& thisPos.y < otherPos.y + other->_size.y
			&& thisPos.y + _size.y > otherPos.y)
				return (true);
			return (false);
		}

		bool BoxCollider2D::collide_AABB2D(CircleCollider *other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 otherPos(other->_transform.position.x + other->_offset.x, other->_transform.position.z + other->_offset.y);
			glm::vec2 nearest(glm::clamp(otherPos.x, thisPos.x, thisPos.x + _size.x), glm::clamp(otherPos.y, thisPos.y, thisPos.y + _size.y));

			if (glm::distance2(nearest, otherPos) < other->_radius * other->_radius)
				return (true);
			return (false);
		}
	}
}