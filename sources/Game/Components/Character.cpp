#include "Game/Components/Character.hpp"
#include "Core/Time.hpp"
#include "Core/GameObject.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Game/Components/Bomb.hpp"
#include "Game/Components/Map.hpp"
#include "Game/Assets.hpp"
#include "Core/Component/RigidBody2D.hpp"
#include "Core/Json/Json.hpp"

namespace Game
{
	namespace Component
	{
        Character::Character(BeerEngine::GameObject *gameObject) :
			Component(gameObject),
            _transform(gameObject->transform),
            _speed(2),
            _bombNb(1),
            _maxBomb(1),
            _explosionSize(1),
            _direction(0, 0),
			bombMesh(nullptr),
			bombMaterial(nullptr),
			map(nullptr)
		{

        }

        void    Character::start(void)
        {
			bombMesh = Assets::GetModel("assets/models/Bomb/bomb.obj");
			bombMaterial = new BeerEngine::Graphics::AMaterial(BeerEngine::Graphics::Graphics::defaultShader);
			bombMaterial->setAlbedo(Assets::GetTexture("assets/models/Bomb/bombbody_BaseColor.png"));
        }

        void    Character::fixedUpdate(void)
        {
            BeerEngine::Component::RigidBody2D *rb2d = _gameObject->GetComponent<BeerEngine::Component::RigidBody2D>();
            if (rb2d)
            {
                if (_direction == glm::vec2(0))
                    rb2d->velocity = glm::vec2(0);
                else
                    rb2d->velocity = glm::normalize(_direction) * _speed;
            }
            _direction = glm::vec2(0, 0);
        }

        void    Character::update(void)
        {
        }

        void    Character::translate(glm::vec3 dir)
        {
            dir = glm::normalize(dir);
            _transform.translate(dir * _speed * BeerEngine::Time::GetDeltaTime());
        }

        void    Character::move(Direction dir)
        {
            switch (dir)
            {
                case Direction::Up:
                    _direction += glm::vec2(0, 1);
                    break;
                
                case Direction::Down:
                    _direction += glm::vec2(0, -1);
                    break;
                
                case Direction::Left:
                    _direction += glm::vec2(1, 0);
                    break;
                
                case Direction::Right:
                    _direction += glm::vec2(-1, 0);
                    break;
            }
        }

        void    Character::increaseSpeed(float val)
        {
            _speed += val;
            if (_speed >= MAX_SPEED)
                _speed = MAX_SPEED;
        }

        void    Character::addBomb(void)
        {
            ++_bombNb;
            if (_bombNb >= _maxBomb)
                _bombNb = _maxBomb;
        }

        void    Character::increaseMaxBomb(void)
        {
            ++_maxBomb;
            ++_bombNb;
            if (_maxBomb >= MAX_BOMBS)
                _maxBomb = MAX_BOMBS;
        }

        void    Character::increaseExplosionSize(float val)
        {
            _explosionSize += val;
            if (_explosionSize >= MAX_EXPLOSION_SIZE)
                _explosionSize = MAX_EXPLOSION_SIZE;
        }

        void    Character::dropBomb(void)
        {
            if (_bombNb <= 0 || map->hasBomb(_gameObject->transform.position))
                return;
            BeerEngine::GameObject *go = _gameObject->instantiate<BeerEngine::GameObject>();
            go->transform.position = glm::round(_gameObject->transform.position);
            go->transform.position.y = 0.25f;
            go->transform.scale = glm::vec3(0.5f);
            auto collider = go->AddComponent<BeerEngine::Component::BoxCollider2D>();
            collider->_exceptions.push_back(_gameObject->GetComponent<BeerEngine::Component::ACollider>());
            auto render = go->AddComponent<BeerEngine::Component::MeshRenderer>();
            // render->setMesh(BeerEngine::Graphics::Graphics::cube);
            // render->setMaterial(Assets::GetInstance()->bombMaterial);
            //PUTAIN DE TRUC QUI SEGFAULT, MES COUILLES SUR TON FRONT DEMERDE TOI MASHALLAH
			render->setMesh(bombMesh);
            render->setMaterial(bombMaterial);

            Bomb *bomb = go->AddComponent<Bomb>();
            bomb->map = map;
            bomb->setPower(_explosionSize);
			bomb->onExplode.bind(&Character::addBomb, this);
            --_bombNb;
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

		nlohmann::json	Character::serialize()
		{
			auto j = Component::serialize();
			j.merge_patch({
				{"componentClass", type},
				{"speed", _speed},
				{"bombNB", _bombNb},
				{"explosionSize", _explosionSize},
				{"direction", _direction},
				{"map", SERIALIZE_BY_ID(map)},
				{"bombMesh", bombMesh},
				{"bombMaterial", bombMaterial},
			});
			return j;
		}

        void Character::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
    	{
			Component::deserialize(j, loader);
            this->_speed = j.at("speed");
            this->_bombNb = j.at("bombNB");
            this->_explosionSize = j.at("explosionSize");
            this->_direction = j.at("direction");
			DESERIALIZE_BY_ID(this->map, Map, "map", loader);
			if (j.find("bombMesh") != j.end())
				this->bombMesh = BeerEngine::Graphics::Mesh::Deserialize(j.at("bombMesh"), loader);
			if (j.find("bombMaterial") != j.end())
				this->bombMaterial = BeerEngine::Graphics::AMaterial::Deserialize(j.at("bombMaterial"), loader);
		}

		REGISTER_COMPONENT_CPP(Character)
    }
}