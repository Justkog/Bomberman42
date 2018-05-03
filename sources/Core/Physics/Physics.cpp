#include "Core/Physics/Physics.hpp"
#include "Core/Component/ACollider.hpp"
#include "Core/Window.hpp"
#include "Core/Camera.hpp"
#include "Core/Input.hpp"

namespace BeerEngine
{
	namespace Physics
	{
		Ray Physics::ScreenToWorldRay(glm::vec2 screenPosition)
		{
			float pointX = screenPosition.x / (WINDOW_WIDTH  * 0.5f) - 1.0f;
			float pointY = screenPosition.y / (WINDOW_HEIGHT * 0.5f) - 1.0f;
			glm::mat4 proj = BeerEngine::Window::GetInstance()->getProjection3D();
			auto cam = BeerEngine::Camera::main;
			glm::mat4 view = glm::lookAt(glm::vec3(0.0f), cam->transform.forward(), cam->transform.top());

			glm::mat4 invVP = glm::inverse(proj * view);
			glm::vec4 screenPos = glm::vec4(pointX, -pointY, 1.0f, 1.0f);
			glm::vec4 worldPos = invVP * screenPos;

			glm::vec3 dir = glm::normalize(glm::vec3(worldPos));
			BeerEngine::Physics::Ray ray;
			ray.origin = BeerEngine::Camera::main->transform.position;
			ray.direction = dir;

			return ray;
		}

		Ray Physics::MouseToWorldRay()
		{
			return ScreenToWorldRay(BeerEngine::Input::mousePosition);
		}

		bool Physics::Raycast(glm::vec3 origin, glm::vec3 direction)
		{
			for (BeerEngine::Component::ACollider *c : BeerEngine::Component::ACollider::_colliders)
			{
				if (c->intersect(glm::vec2(origin.x, origin.z), glm::vec2(direction.x, direction.z)))
					return (true);
			}
			return (false);
		}

		bool Physics::Raycast(glm::vec3 origin, glm::vec3 direction, BeerEngine::Component::ACollider** collision)
		{
			glm::vec2 origin2D = glm::vec2(origin.x, origin.z);
			glm::vec2 direction2D = glm::vec2(direction.x, direction.z);
			float bestDist = 0;

			*collision = nullptr;
			for (BeerEngine::Component::ACollider *c : BeerEngine::Component::ACollider::_colliders)
			{
				glm::vec2 pos;
				if (c->intersect(origin2D, direction2D, pos))
				{
					float dist = glm::distance2(origin2D, pos);
					if (*collision == nullptr || dist < bestDist)
					{
						*collision = c;
						bestDist = dist;
					}
				}
			}
			return (*collision == nullptr ? false : true);
		}

		std::vector<BeerEngine::Component::ACollider*> Physics::RaycastAll(glm::vec3 origin, glm::vec3 direction)
		{
			std::vector<BeerEngine::Component::ACollider*> collisions;

			for (BeerEngine::Component::ACollider *c : BeerEngine::Component::ACollider::_colliders)
			{
				if (c->intersect(glm::vec2(origin.x, origin.z), glm::vec2(direction.x, direction.z)))
					collisions.push_back(c);
			}
			return (collisions);
		}
	}
}