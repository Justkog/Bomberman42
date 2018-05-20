#include "Core/Component/CircleCollider.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/GameObject.hpp"
#include "Core/Json/Json.hpp"
#include "Core/Component/Component.hpp"

namespace BeerEngine
{
	namespace Component
	{
		CircleCollider::CircleCollider(GameObject *gameObject) :
			ACollider(gameObject),
			_radius((gameObject->transform.scale.x + gameObject->transform.scale.z) / 4)
		{}

		// CircleCollider::CircleCollider()
		// {}

		// CircleCollider::CircleCollider(const CircleCollider &val)
		// {
		// 	*this = val;
		// }
		
		// CircleCollider &CircleCollider::operator=(const CircleCollider &val)
		// {
		// 	if (this != &val)
		// 	{
		// 		_radius = val._radius;
		// 	}
		// 	return (*this);
		// }

		CircleCollider::~CircleCollider()
		{}

		bool CircleCollider::checkCollision(ACollider *other, bool response)
		{
			if (other->collide_AABB2D(this, response))
				return (true);
			else
				return (false);
		}

		bool CircleCollider::contain(glm::vec2 other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);

			if (glm::distance2(thisPos, other) < _radius * _radius)
				return (true);
			return (false);
		}

		bool CircleCollider::lineCollision(glm::vec2 A, glm::vec2 B, glm::vec2 C)
		{
			glm::vec2 u = B - A;
			glm::vec2 AC = C - A;
			float numerator = std::abs(u.x * AC.y - u.y * AC.x);
			float denominator = glm::length(u);
			float CI = numerator / denominator;

			return (CI < _radius);
		}

		bool CircleCollider::segmentCollision(glm::vec2 A, glm::vec2 B, glm::vec2 C)
		{
			if (!lineCollision(A, B, C))
				return (false);

			glm::vec2 AB = B - A;
			glm::vec2 AC = C - A;
			glm::vec2 BC = C - B;
			float scalar1 = AB.x * AC.x + AB.y * AC.y;
			float scalar2 = (-AB.x) * BC.x + (-AB.y) * BC.y;
			if (scalar1 >= 0 && scalar2 >= 0)
				return (true);
			if (contain(A) || contain(B))
				return (true);
			return (false);
		}

		bool CircleCollider::intersect(glm::vec2 origin, glm::vec2 dir)
		{
			glm::vec2 pos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);

			return (segmentCollision(origin, origin + dir, pos));
		}

		bool CircleCollider::intersect(glm::vec2 origin, glm::vec2 dir, glm::vec2 &outPosition)
		{
			glm::vec2 pos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);

			outPosition = pos;
			return (segmentCollision(origin, origin + dir, pos));
		}

		bool CircleCollider::collide_AABB2D(CircleCollider *other, bool response)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 otherPos(other->_transform.position.x + other->_offset.x, other->_transform.position.z + other->_offset.y);

			if (glm::distance2(thisPos, otherPos) < (_radius + other->_radius) * (_radius + other->_radius))
			{
				if (response && !_isTrigger && !other->_isTrigger)
					response_AABB2D(other, thisPos, otherPos);
				return (true);
			}
			return (false);
		}

		bool CircleCollider::collide_AABB2D(BoxCollider2D *other, bool response)
		{
			return (other->collide_AABB2D(this, response));
		}

		void CircleCollider::response_AABB2D(CircleCollider *other, glm::vec2 &thisPos, glm::vec2 &otherPos)
		{
			float overlap = (_radius + other->_radius) - glm::distance(thisPos, otherPos);
			glm::vec3 dir(thisPos.x - otherPos.x, 0, thisPos.y - otherPos.y);
			dir = glm::normalize(dir);
			
			response(other, dir * overlap);
		}

		nlohmann::json	CircleCollider::serialize()
		{
			auto j = ACollider::serialize();
			j.merge_patch({
				{"componentClass", type},
				{"radius", _radius},
			});
			return j;
		}

		void CircleCollider::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			this->ACollider::deserialize(j, loader);
			this->_radius = j.at("radius");
		}

		REGISTER_COMPONENT_CPP(CircleCollider)
	}
}