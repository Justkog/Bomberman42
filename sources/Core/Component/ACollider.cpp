#include "Core/Component/ACollider.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/GameObject.hpp"
#include "Core/Component/ITriggerStay.hpp"
#include "Core/Component/ITriggerEnter.hpp"
#include "Core/Component/ITriggerExit.hpp"


namespace BeerEngine
{
	namespace Component
	{
		std::vector<ACollider*> ACollider::_colliders;

		ACollider::ACollider(GameObject *gameObject) :
			Component(gameObject),
			_offset(glm::vec2(0, 0)),
			_transform(gameObject->transform),
			_collide(false)
		{
			_id = _colliders.size();
			_colliders.push_back(this);
		}

		void    ACollider::physicUpdate(void)
		{
			for (int i = _id + 1; i < _colliders.size(); i++)
			{
				auto other = _colliders[i];
				if (checkCollision(other))
				{
					triggerStay();
					other->triggerStay();

					auto c = std::find(_currentCollisions.begin(), _currentCollisions.end(), other);
					if (c == _currentCollisions.end())
					{
						_currentCollisions.push_back(other);
						triggerEnter();
						other->triggerEnter();
					}
				}
				else
				{
					auto c = std::find(_currentCollisions.begin(), _currentCollisions.end(), other);
					if (c != _currentCollisions.end())
					{
						_currentCollisions.erase(c);
						triggerExit();
						other->triggerExit();
					}
				}
			}
		}

		void ACollider::triggerStay(void)
		{
			auto GOcomponents = _gameObject->GetComponents();
			for (Component::Component *c : GOcomponents)
			{
				if (auto r = dynamic_cast<BeerEngine::Component::ITriggerStay *>(c))
				{
					r->onTriggerStay();
				}
			}
		}

		void ACollider::triggerEnter(void)
		{
			auto GOcomponents = _gameObject->GetComponents();
			for (Component::Component *c : GOcomponents)
			{
				if (auto r = dynamic_cast<BeerEngine::Component::ITriggerEnter *>(c))
				{
					r->onTriggerEnter();
				}
			}
		}

		void ACollider::triggerExit(void)
		{
			auto GOcomponents = _gameObject->GetComponents();
			for (Component::Component *c : GOcomponents)
			{
				if (auto r = dynamic_cast<BeerEngine::Component::ITriggerExit *>(c))
				{
					r->onTriggerExit();
				}
			}
		}
	}
}