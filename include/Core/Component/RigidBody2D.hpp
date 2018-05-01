#ifndef BE_CORE_COMPONENT_RIGIDBODY2D_HPP
#define BE_CORE_COMPONENT_RIGIDBODY2D_HPP 1

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"

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

			virtual nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif
