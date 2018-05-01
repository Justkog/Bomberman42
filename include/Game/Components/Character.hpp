#ifndef BE_GAME_COMPONENT_CHARACTER_HPP
#define BE_GAME_COMPONENT_CHARACTER_HPP 1

#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/ITriggerStay.hpp"
#include "Core/Component/ITriggerEnter.hpp"
#include "Core/Component/ITriggerExit.hpp"
#include "Core/Component/IColliderStay.hpp"
#include "Core/Component/IColliderEnter.hpp"
#include "Core/Component/IColliderExit.hpp"
#include "Core/GameObject.hpp"
#include "Core/Transform.hpp"

#define MAX_SPEED 4
#define MAX_BOMBS 20
#define MAX_EXPLOSION_SIZE 8

namespace Game
{
	namespace Component
	{
		class Character : public BeerEngine::Component::Component,
						public BeerEngine::Component::IStart,
						public BeerEngine::Component::IUpdate,
						public BeerEngine::Component::ITriggerStay,
						public BeerEngine::Component::ITriggerEnter,
						public BeerEngine::Component::ITriggerExit,
						public BeerEngine::Component::IColliderStay,
						public BeerEngine::Component::IColliderEnter,
						public BeerEngine::Component::IColliderExit
		{
		protected:
			BeerEngine::Transform &_transform;

		public:
            Character(BeerEngine::GameObject *gameObject);

            virtual void    start(void);
            virtual void    fixedUpdate(void);
       		virtual void    update(void);

			void	translate(glm::vec3 dir);
			void    increaseSpeed(float val);
			void    addBomb(int nb);
			void    increaseExplosionSize(float val);
			
       		virtual void    onTriggerStay(BeerEngine::Component::ACollider *other);
       		virtual void    onTriggerEnter(BeerEngine::Component::ACollider *other);
       		virtual void    onTriggerExit(BeerEngine::Component::ACollider *other);
       		virtual void    onColliderStay(BeerEngine::Component::ACollider *other);
       		virtual void    onColliderEnter(BeerEngine::Component::ACollider *other);
       		virtual void    onColliderExit(BeerEngine::Component::ACollider *other);

			float _speed;
			unsigned int _bombNb;
			float _explosionSize;

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif