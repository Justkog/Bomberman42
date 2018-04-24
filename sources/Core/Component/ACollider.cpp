#include "Core/Component/ACollider.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		ACollider::ACollider(GameObject *gameObject) :
			Component(gameObject),
			_offset(glm::vec2(1, 1)),
			_transform(gameObject->transform)
		{
			_colliders.push_back(this);
		}
	}
}