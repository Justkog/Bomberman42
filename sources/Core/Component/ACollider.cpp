#include "Core/Component/ACollider.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		ACollider::ACollider(GameObject *gameObject) :
			Component(gameObject),
			_offset(glm::vec2(1, 1)),
			_transform(gameObject->transform)
		{}

		void    		ACollider::fixedUpdate(void)
		{
		}

		void    		ACollider::update(void)
		{
		}
	}
}