#include "Core/Component/ACollider.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/GameObject.hpp"
#include "Core/Component/ITriggerStay.hpp"
#include "Core/Component/ITriggerEnter.hpp"
#include "Core/Component/ITriggerExit.hpp"
#include "Core/Component/IColliderStay.hpp"
#include "Core/Component/IColliderEnter.hpp"
#include "Core/Component/IColliderExit.hpp"
#include "Core/Json/Json.hpp"

namespace BeerEngine
{
	namespace Component
	{
		std::vector<ACollider*> ACollider::_colliders;

		ACollider::ACollider(GameObject *gameObject) :
			Component(gameObject),
			_transform(gameObject->transform),
			_offset(glm::vec2(0, 0)),
			_isTrigger(false),
			_kinematic(true)
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
					if (_isTrigger)
						triggerStay(other);
					else
						colliderStay(other);
					if (other->_isTrigger)
						other->triggerStay(this);
					else
						other->colliderStay(this);

					auto c = std::find(_currentCollisions.begin(), _currentCollisions.end(), other);
					if (c == _currentCollisions.end())
					{
						_currentCollisions.push_back(other);
						if (_isTrigger)
							triggerEnter(other);
						else
							colliderEnter(other);
						if (other->_isTrigger)
							other->triggerEnter(this);
						else
							other->colliderEnter(this);
					}
				}
				else
				{
					auto c = std::find(_currentCollisions.begin(), _currentCollisions.end(), other);
					if (c != _currentCollisions.end())
					{
						_currentCollisions.erase(c);
						if (_isTrigger)
							triggerExit(other);
						else
							colliderExit(other);
						if (other->_isTrigger)
							other->triggerExit(this);
						else
							other->colliderExit(this);
					}
				}
			}
		}

		void ACollider::triggerStay(ACollider *other)
		{
			auto GOcomponents = _gameObject->GetComponents();
			for (Component *c : GOcomponents)
			{
				if (auto r = dynamic_cast<BeerEngine::Component::ITriggerStay *>(c))
				{
					r->onTriggerStay(other);
				}
			}
		}

		void ACollider::triggerEnter(ACollider *other)
		{
			auto GOcomponents = _gameObject->GetComponents();
			for (Component *c : GOcomponents)

			for (Component *c : GOcomponents)
			{
				if (auto r = dynamic_cast<BeerEngine::Component::ITriggerEnter *>(c))
				{
					r->onTriggerEnter(other);
				}
			}
		}

		void ACollider::triggerExit(ACollider *other)
		{
			auto GOcomponents = _gameObject->GetComponents();
			for (Component *c : GOcomponents)
			{
				if (auto r = dynamic_cast<BeerEngine::Component::ITriggerExit *>(c))
				{
					r->onTriggerExit(other);
				}
			}
		}

		void ACollider::colliderStay(ACollider *other)
		{
			auto GOcomponents = _gameObject->GetComponents();
			for (Component *c : GOcomponents)
			{
				if (auto r = dynamic_cast<BeerEngine::Component::IColliderStay *>(c))
				{
					r->onColliderStay(other);
				}
			}
		}

		void ACollider::colliderEnter(ACollider *other)
		{
			auto GOcomponents = _gameObject->GetComponents();
			for (Component *c : GOcomponents)
			{
				if (auto r = dynamic_cast<BeerEngine::Component::IColliderEnter *>(c))
				{
					r->onColliderEnter(other);
				}
			}
		}

		void ACollider::colliderExit(ACollider *other)
		{
			auto GOcomponents = _gameObject->GetComponents();
			for (Component *c : GOcomponents)
			{
				if (auto r = dynamic_cast<BeerEngine::Component::IColliderExit *>(c))
				{
					r->onColliderExit(other);
				}
			}
		}
	}
}
