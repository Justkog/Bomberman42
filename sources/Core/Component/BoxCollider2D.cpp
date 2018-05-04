#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/Component/ITriggerStay.hpp"
#include "Core/Component/ITriggerEnter.hpp"
#include "Core/Component/ITriggerExit.hpp"
#include "Core/GameObject.hpp"
#include "Core/Json/Json.hpp"

#include <vector>

namespace BeerEngine
{
	namespace Component
	{
		BoxCollider2D::BoxCollider2D(GameObject *gameObject) :
			ACollider(gameObject),
			_size(glm::vec2(gameObject->transform.scale.x, gameObject->transform.scale.z))
		{}

		BoxCollider2D::~BoxCollider2D()
		{}

		bool BoxCollider2D::checkCollision(ACollider *other)
		{
			if (other->collide_AABB2D(this))
				return (true);
			else
				return (false);
		}

		bool BoxCollider2D::contain(glm::vec2 other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);

			if (thisPos.x - _size.x / 2 > other.x
			|| thisPos.x + _size.x / 2 < other.x
			|| thisPos.y - _size.y / 2 > other.y
			|| thisPos.y + _size.y / 2 < other.y)
				return (false);
			return (true);
		}

		bool BoxCollider2D::intersect(glm::vec2 origin, glm::vec2 dir)
		{
			glm::vec2 pos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 dest(origin.x + dir.x, origin.y + dir.y);
			glm::vec2 posMin(pos.x - _size.x / 2, pos.y - _size.y / 2);
			glm::vec2 posMax(pos.x + _size.x / 2, pos.y + _size.y / 2);
			float m = (dest.y - origin.y) / (dest.x - origin.x);

			if ((posMin.x > dest.x && posMin.x > origin.x) || (posMin.y > dest.y && posMin.y > origin.y)
			|| (posMax.x < dest.x && posMax.x < origin.x) || (posMax.y < dest.y && posMax.y < origin.y))
				return (false);

			float y = m * (posMin.x - origin.x) + origin.y;
			if (y > posMin.y && y < posMax.y) return (true);
			y = m * (posMax.x - origin.x) + origin.y;
			if (y > posMin.y && y < posMax.y) return (true);
			float x = (posMin.y - origin.y) / m + origin.x;
			if (x > posMin.x && x < posMax.x) return (true);
			x = (posMax.y - origin.y) / m + origin.x;
			if (x > posMin.x && x < posMax.x) return (true);

			return (false);
		}

		bool BoxCollider2D::intersect(glm::vec2 origin, glm::vec2 dir, glm::vec2 &outPosition)
		{
			glm::vec2 pos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 dest(origin.x + dir.x, origin.y + dir.y);
			glm::vec2 posMin(pos.x - _size.x / 2, pos.y - _size.y / 2);
			glm::vec2 posMax(pos.x + _size.x / 2, pos.y + _size.y / 2);
			float m = (dest.y - origin.y) / (dest.x - origin.x);

			outPosition = pos;
			if ((posMin.x > dest.x && posMin.x > origin.x) || (posMin.y > dest.y && posMin.y > origin.y)
			|| (posMax.x < dest.x && posMax.x < origin.x) || (posMax.y < dest.y && posMax.y < origin.y))
				return (false);

			float y = m * (posMin.x - origin.x) + origin.y;
			if (y > posMin.y && y < posMax.y) return (true);
			y = m * (posMax.x - origin.x) + origin.y;
			if (y > posMin.y && y < posMax.y) return (true);
			float x = (posMin.y - origin.y) / m + origin.x;
			if (x > posMin.x && x < posMax.x) return (true);
			x = (posMax.y - origin.y) / m + origin.x;
			if (x > posMin.x && x < posMax.x) return (true);

			return (false);
		}

		bool BoxCollider2D::collide_AABB2D(BoxCollider2D *other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 otherPos(other->_transform.position.x + other->_offset.x, other->_transform.position.z + other->_offset.y);

			if (thisPos.x - _size.x / 2 > otherPos.x + other->_size.x / 2
			|| thisPos.x + _size.x / 2 < otherPos.x - other->_size.x / 2
			|| thisPos.y - _size.y / 2 > otherPos.y + other->_size.y / 2
			|| thisPos.y + _size.y / 2 < otherPos.y - other->_size.y / 2)
				return (false);
			if (!_isTrigger && !other->_isTrigger)
				response_AABB2D(other, thisPos, otherPos);
			return (true);
		}

		bool BoxCollider2D::collide_AABB2D(CircleCollider *other)
		{
			glm::vec2 thisPos(_transform.position.x + _offset.x, _transform.position.z + _offset.y);
			glm::vec2 otherPos(other->_transform.position.x + other->_offset.x, other->_transform.position.z + other->_offset.y);
			glm::vec2 nearest(glm::clamp(otherPos.x, thisPos.x - _size.x / 2, thisPos.x + _size.x / 2), glm::clamp(otherPos.y, thisPos.y - _size.y / 2, thisPos.y + _size.y / 2));

			if (glm::distance2(nearest, otherPos) < other->_radius * other->_radius)
			{
				if (!_isTrigger && !other->_isTrigger)
					response_AABB2D(other, nearest, otherPos);
				return (true);
			}
			return (false);
		}

		void BoxCollider2D::response_AABB2D(BoxCollider2D *other, glm::vec2 &thisPos, glm::vec2 &otherPos)
		{
			glm::vec3 move(0, 0, 0);

			if (thisPos.x >= otherPos.x && thisPos.x - _size.x / 2 < otherPos.x + other->_size.x / 2)
				move.x = otherPos.x + other->_size.x / 2 - (thisPos.x - _size.x / 2);
			if (thisPos.x < otherPos.x && thisPos.x + _size.x / 2 > otherPos.x - other->_size.x / 2)
				move.x = otherPos.x - other->_size.x / 2 - (thisPos.x + _size.x / 2);
			if (thisPos.y >= otherPos.y && thisPos.y - _size.y / 2 < otherPos.y + other->_size.y / 2)
				move.z = otherPos.y + other->_size.y / 2 - (thisPos.y - _size.y / 2);
			if (thisPos.y < otherPos.y && thisPos.y + _size.y / 2 > otherPos.y - other->_size.y / 2)
				move.z = otherPos.y - other->_size.y / 2 - (thisPos.y + _size.y / 2);
			if (abs(move.x) >= abs(move.z))
				move.x = 0;
			else
				move.z = 0;

			// if (rb2d != nullptr)
			// {
			// 	rb2d->velocity = glm::vec2(0.0f);
			// }
			// if (other->rb2d != nullptr)
			// {
			// 	other->rb2d->velocity = glm::vec2(0.0f);
			// }

			// if (other->isKinematic() && !isKinematic())
			// {
			// 	_transform.translate(move);
			// }
			// else if (!other->isKinematic() && isKinematic())
			// {
			// 	other->_transform.translate(-move);
			// }
			// else if (!other->isKinematic() && !isKinematic())
			// {
			// 	_transform.translate(move / 2);
			// 	other->_transform.translate(-move / 2);
			// }
			response(other, move);
		}

		void BoxCollider2D::response_AABB2D(CircleCollider *other, glm::vec2 &nearest, glm::vec2 &otherPos)
		{
			float overlap = other->_radius - glm::distance(nearest, otherPos);
			glm::vec3 dir(nearest.x - otherPos.x, 0, nearest.y - otherPos.y);
			dir = glm::normalize(dir);

			response(other, dir * overlap);
			// if (other->isKinematic() && !isKinematic())
			// 	_transform.translate(dir * overlap);
			// else if (!other->isKinematic() && isKinematic())
			// 	other->_transform.translate(-dir * overlap);
			// else if (!other->isKinematic() && !isKinematic())
			// {
			// 	_transform.translate(dir * (overlap / 2));
			// 	other->_transform.translate(-dir * (overlap / 2));
			// }
		}

		nlohmann::json	BoxCollider2D::serialize()
		{
			return {
				{"componentClass", typeid(BoxCollider2D).name()},
				{"size", _size},
			};
		}

		void BoxCollider2D::deserialize(const nlohmann::json & j)
		{
			this->_size = j.at("size");
		}

		REGISTER_COMPONENT_CPP(BoxCollider2D)
	}
}