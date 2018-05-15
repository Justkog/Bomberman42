#include "Core/Component/RigidBody2D.hpp"
#include "Core/GameObject.hpp"
#include "Core/Json/Json.hpp"

namespace BeerEngine
{
	namespace Component
	{
		RigidBody2D::RigidBody2D(GameObject *gameObject) :
			Component(gameObject),
			velocity(0.0f, 0.0f),
			kinematic(RBType::Kinematic),
			mass(1.0f)
		{}

		void    RigidBody2D::physicUpdate(void)
		{
			float dist = glm::length(velocity);
			if (dist == 0.0f)
				return;
			glm::vec3 move(velocity[0] / 60.0f, 0.0f, velocity[1] / 60.0f);
			_gameObject->transform.translate(move);

			glm::vec2 velocityDir = glm::normalize(velocity);
			float ndist = dist - (dist / 60.0f);
			velocity = velocityDir * ndist;
		}

		nlohmann::json	RigidBody2D::serialize()
		{
			auto j = Component::serialize();
			j.merge_patch({
				{"componentClass", type},
				{"velocity", velocity},
				{"kinematic", kinematic},
				{"mass", mass},
			});
			return j;
		}

		void RigidBody2D::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			this->Component::deserialize(j, loader);
			this->velocity = j.at("velocity");
			this->kinematic = j.at("kinematic");
			this->mass = j.at("mass");
		}

		REGISTER_COMPONENT_CPP(RigidBody2D)
	}
}
