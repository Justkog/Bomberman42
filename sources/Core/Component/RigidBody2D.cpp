#include "Core/Component/RigidBody2D.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		RigidBody2D::RigidBody2D(GameObject *gameObject) :
			Component(gameObject),
			velocity(0.0f, 0.0f),
			kinematic(true),
			mass(1.0f)
		{}

		void    RigidBody2D::physicUpdate(void)
		{
			float dist = glm::length(velocity);
			if (dist == 0.0f)
				return ;
			glm::vec3 move(velocity[0], 0.0f, velocity[1]);
			_gameObject->transform.translate(move / 60.0f);

			glm::vec2 velocityDir = glm::normalize(velocity);
			float ndist = dist - (dist / 60.0f);
			velocity = velocityDir * ndist;
		}
	}
}