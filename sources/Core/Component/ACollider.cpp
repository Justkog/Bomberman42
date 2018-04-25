#include "Core/Component/ACollider.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		std::vector<ACollider*> ACollider::_colliders;

		ACollider::ACollider(GameObject *gameObject) :
			Component(gameObject),
			_offset(glm::vec2(0, 0)),
			_transform(gameObject->transform),
			_collide(false)
		{
			_colliders.push_back(this);
		}
	}
}