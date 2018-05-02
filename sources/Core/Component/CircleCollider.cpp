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

		CircleCollider::~CircleCollider()
		{}

		bool CircleCollider::checkCollision(ACollider *other)
		{
			if (other->collide_AABB2D(this))
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

		bool CircleCollider::intersect(glm::vec2 origin, glm::vec2 dir)
		{
			// glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);

			// dir = glm::normalize(dir);
			// if (thisPos.x - _size.x / 2 > origin.x + (dir.x * dist)
			// || thisPos.x + _size.x / 2 < origin.x
			// || thisPos.y - _size.y / 2 > origin.y + (dir.y * dist)
			// || thisPos.y + _size.y / 2 < origin.y)
			// 	return (false);
			// return (true);
		}

		bool CircleCollider::collide_AABB2D(CircleCollider *other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 otherPos(other->_transform.position.x + other->_offset.x, other->_transform.position.z + other->_offset.y);

			if (glm::distance2(thisPos, otherPos) < (_radius + other->_radius) * (_radius + other->_radius))
			{
				if (!_isTrigger && !other->_isTrigger)
					response_AABB2D(other, thisPos, otherPos);
				return (true);
			}
			return (false);
		}

		bool CircleCollider::collide_AABB2D(BoxCollider2D *other)
		{
			return (other->collide_AABB2D(this));
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
			return {
				{"componentClass", typeid(CircleCollider).name()},
				{"radius", _radius},
			};
		}

		void CircleCollider::deserialize(const nlohmann::json & j)
		{
			this->_radius = j.at("radius");
		}

		REGISTER_COMPONENT_CPP(CircleCollider)
	}
}