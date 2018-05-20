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
#include "Core/Component/RigidBody2D.hpp"
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
			_isTrigger(false)
		{
			_colliders.push_back(this);
			colliderType = ALL;
			rb2d = nullptr;
		}

		ACollider::ACollider() :
		 	 _transform(Transform::basic)
		{}

		ACollider::ACollider(const ACollider &val) :
			_transform(val._transform)
		{
			*this = val;
		}
		
		ACollider &ACollider::operator=(const ACollider &val)
		{
			if (this != &val)
			{
				_currentCollisions.clear();
				_exceptions.clear();
				for (std::size_t i = 0; i < val._currentCollisions.size(); i++)
					_currentCollisions.push_back(val._currentCollisions[i]);
				for (std::size_t i = 0; i < val._exceptions.size(); i++)
					_exceptions.push_back(val._exceptions[i]);
				_transform = val._transform;
				_offset = val._offset;
				_isTrigger = val._isTrigger;
				rb2d = val.rb2d;
				colliderType = val.colliderType;
			}
			return (*this);
		}

		ACollider::~ACollider()
		{
			auto it = std::find(_colliders.begin(), _colliders.end(), this);
			if (it != _colliders.end())
				_colliders.erase(it);
			for (ACollider *other : _currentCollisions)
			{
				if ((it = std::find(other->_currentCollisions.begin(), other->_currentCollisions.end(), this)) != other->_currentCollisions.end())
				{
					other->_currentCollisions.erase(it);
				}
			}
		}

		void    ACollider::start(void)
		{
			rb2d = _gameObject->GetComponent<RigidBody2D>();
		}

		void    ACollider::physicUpdate(void)
		{
			auto it = std::find(_colliders.begin(), _colliders.end(), this);
			++it;
			for (std::size_t i = it - _colliders.begin(); i < _colliders.size(); i++)
			{
				auto other = _colliders[i];
				// On check les type de collision entre eux
				if (colliderType == ALL)
				{
					if (other->colliderType == ONLY_THERE)
						continue;
				}
				else if (colliderType == ONLY_OTHER)
				{
					if (other->colliderType == ONLY_OTHER
						|| other->colliderType == ONLY_THERE)
						continue;
				}
				else if (colliderType == ONLY_THERE)
				{
					if (other->colliderType != ONLY_THERE)
						continue;
				}

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
						other->_currentCollisions.push_back(this);
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
						if ((c = std::find(other->_currentCollisions.begin(), other->_currentCollisions.end(), this)) != other->_currentCollisions.end())
							other->_currentCollisions.erase(c);
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

		bool ACollider::hasException(ACollider *other)
		{
			auto it = std::find(_exceptions.begin(), _exceptions.end(), other);
			if (it != _exceptions.end())
				return (true);
			it = std::find(other->_exceptions.begin(), other->_exceptions.end(), this);
			if (it != other->_exceptions.end())
				return (true);
			return (false);
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

		bool ACollider::isKinematic(void)
		{
			if (rb2d != nullptr)
			{
				if (rb2d->kinematic == RBType::Static)
					return (rb2d->velocity == glm::vec2(0));
				return (rb2d->kinematic == RBType::Kinematic ? true : false);
			}
			return (true);
		}

		void ACollider::response(ACollider *other, glm::vec3 move)
		{
			if (hasException(other))
				return;

			if (move.x != move.x || move.y != move.y || move.z != move.z)
				return;

			if (other->isKinematic() && !isKinematic())
			{
				_transform.translate(move);
				if (move[0] != 0)
					rb2d->velocity[0] = 0.0f;
				else
					rb2d->velocity[1] = 0.0f;
			}
			else if (!other->isKinematic() && isKinematic())
			{
				other->_transform.translate(-move);
				if (move[0] != 0)
					other->rb2d->velocity[0] = 0.0f;
				else
					other->rb2d->velocity[1] = 0.0f;
			}
			else if (!other->isKinematic() && !isKinematic())
			{
				float totalMass = other->rb2d->mass + rb2d->mass;
				float a = rb2d->mass / totalMass;
				float b = other->rb2d->mass / totalMass;
				_transform.translate(move * b);
				other->_transform.translate(-move * a);
			}
		}

		nlohmann::json	ACollider::serialize()
		{
			auto j = Component::serialize();
			j.merge_patch({
				{"isTrigger", _isTrigger},
			});
			return j;
		}

		void ACollider::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			this->Component::deserialize(j, loader);
			this->_isTrigger = j.at("isTrigger");
		}
	}
}
