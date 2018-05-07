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

		bool Physics::Raycast(glm::vec3 origin, glm::vec3 direction, RaycastHit &hit)
		{
			glm::vec2 origin2D = glm::vec2(origin.x, origin.z);
			glm::vec2 direction2D = glm::vec2(direction.x, direction.z);
			float bestDist = -1;

			for (BeerEngine::Component::ACollider *c : BeerEngine::Component::ACollider::_colliders)
			{
				glm::vec2 pos;
				if (c->intersect(origin2D, direction2D, pos))
				{
					float dist = glm::distance2(origin2D, pos);
					if (bestDist == -1 || dist < bestDist)
					{
						hit.collider = c;
						hit.transform = &(c->_transform);
						hit.distance = glm::distance(origin2D, pos);
						bestDist = dist;
					}
				}
			}
			return (bestDist == -1 ? false : true);
		}

		bool Physics::Raycast(glm::vec3 origin, glm::vec3 direction, RaycastHit &hit, int n)
		{
			std::vector<RaycastHit> collisions;
			glm::vec2 origin2D = glm::vec2(origin.x, origin.z);
			glm::vec2 direction2D = glm::vec2(direction.x, direction.z);

			for (BeerEngine::Component::ACollider *c : BeerEngine::Component::ACollider::_colliders)
			{
				glm::vec2 pos;
				if (c->intersect(origin2D, direction2D, pos))
					collisions.push_back(RaycastHit(c, &(c->_transform), glm::distance(origin2D, pos)));
			}
			std::sort(collisions.begin(), collisions.end());
			if (n < collisions.size())
			{
				hit = collisions[n];
				return (true);
			}
			return (false);
		}

		std::vector<RaycastHit> Physics::RaycastAll(glm::vec3 origin, glm::vec3 direction)
		{
			std::vector<RaycastHit> collisions;
			glm::vec2 origin2D = glm::vec2(origin.x, origin.z);
			glm::vec2 direction2D = glm::vec2(direction.x, direction.z);

			for (BeerEngine::Component::ACollider *c : BeerEngine::Component::ACollider::_colliders)
			{
				glm::vec2 pos;
				if (c->intersect(origin2D, direction2D, pos))
					collisions.push_back(RaycastHit(c, &(c->_transform), glm::distance(origin2D, pos)));
			}
			return (collisions);
		}

		std::vector<RaycastHit> Physics::RaycastAllOrdered(glm::vec3 origin, glm::vec3 direction)
		{
			std::vector<RaycastHit> collisions;
			glm::vec2 origin2D = glm::vec2(origin.x, origin.z);
			glm::vec2 direction2D = glm::vec2(direction.x, direction.z);

			for (BeerEngine::Component::ACollider *c : BeerEngine::Component::ACollider::_colliders)
			{
				glm::vec2 pos;
				if (c->intersect(origin2D, direction2D, pos))
					collisions.push_back(RaycastHit(c, &(c->_transform), glm::distance(origin2D, pos)));
			}
			std::sort(collisions.begin(), collisions.end());
			return (collisions);
		}
	}
}