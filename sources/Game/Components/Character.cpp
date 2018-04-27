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
            std::cout << "Increase Speed by " << val << ". _speed = " << _speed << std::endl;
        }

        void    Character::addBomb(int nb)
        {
            _bombNb += nb;
            if (_bombNb >= MAX_BOMBS)
                _bombNb = MAX_BOMBS;
            std::cout << "Add " << nb << " Bomb. _bombNb = " << _bombNb << std::endl;
        }

        void    Character::increaseExplosionSize(float val)
        {
            _explosionSize += val;
            if (_explosionSize >= MAX_EXPLOSION_SIZE)
                _explosionSize = MAX_EXPLOSION_SIZE;
            std::cout << "Increase Explosion Size by " << val << ". _explosionSize = " << _explosionSize << std::endl;
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