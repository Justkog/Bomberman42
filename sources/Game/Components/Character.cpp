#include "Game/Components/Character.hpp"
#include "Core/Time.hpp"

namespace Game
{
	namespace Component
	{
        Character::Character(BeerEngine::GameObject *gameObject) :
			Component(gameObject),
            _transform(gameObject->transform),
            _speed(2),
            _bombNb(5),
            _explosionSize(2)
		{

        }

        void    Character::start(void)
        {
        }

        void    Character::fixedUpdate(void)
        {
            
        }

        void    Character::update(void)
        {
        }

        void    Character::translate(glm::vec3 dir)
        {
            glm::normalize(dir);
            _transform.translate(dir * _speed * BeerEngine::Time::GetDeltaTime());
        }

        void    Character::increaseSpeed(float val)
        {
            _speed += val;
            if (_speed >= MAX_SPEED)
                _speed = MAX_SPEED;
        }

        void   Character::onTriggerStay(BeerEngine::Component::ACollider *other)
        {
        }

        void   Character::onTriggerEnter(BeerEngine::Component::ACollider *other)
        {
        }

        void   Character::onTriggerExit(BeerEngine::Component::ACollider *other)
        {
        }

        void   Character::onColliderStay(BeerEngine::Component::ACollider *other)
        {
        }

        void   Character::onColliderEnter(BeerEngine::Component::ACollider *other)
        {
        }

        void   Character::onColliderExit(BeerEngine::Component::ACollider *other)
        {
        }
    }
}