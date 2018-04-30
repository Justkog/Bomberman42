#ifndef BE_CORE_COMPONENT_RIGIDBODY2D_HPP
#define BE_CORE_COMPONENT_RIGIDBODY2D_HPP 1

#include "../BeerEngine.hpp"
#include "Component.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class RigidBody2D : public Component
		{
		public:
			glm::vec2	velocity;
			bool		kinematic;
			float		mass;

		public:
			RigidBody2D(GameObject *gameObject);
			void    physicUpdate(void);

		};
	}
}

#endif
