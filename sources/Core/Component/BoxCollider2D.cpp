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
			int nbCollision = 0;

			for (int i = 0; i < _colliders.size(); ++i)
			{
				auto other = _colliders[i];
				if (other == this)
					continue;
				if (other->collide_AABB2D(this))
				{
					nbCollision++;
					_collide = true;
					_gameObject->GetComponent<BeerEngine::Component::MeshRenderer>()
					->getMaterial()->setColor(glm::vec4(1, 0, 0, 1));
					// auto collisionTriggers = other->_gameObject->GetComponents<ICollision>();
					// for (auto comp: collisionTriggers)
					// {
					// 	// call onCollisionStay
					// }
				}
			}
			if (!nbCollision)
			{
				_collide = false;
				_gameObject->GetComponent<BeerEngine::Component::MeshRenderer>()
				->getMaterial()->setColor(glm::vec4(1, 1, 1, 1));
			}
		}

		bool BoxCollider2D::collide_AABB2D(BoxCollider2D *other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 otherPos(other->_transform.position.x + other->_offset.x, other->_transform.position.z + other->_offset.y);

			if (thisPos.x > otherPos.x + other->_size.x
			|| thisPos.x + _size.x < otherPos.x
			|| thisPos.y > otherPos.y + other->_size.y
			|| thisPos.y + _size.y < otherPos.y)
				return (false);
			
			return (true);
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