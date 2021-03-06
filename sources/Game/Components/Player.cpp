#include "Game/Components/Player.hpp"
#include "Game/Components/Character.hpp"
#include "Game/Components/GameManager.hpp"
#include "Core/Input.hpp"
#include "Core/GameObject.hpp"
#include "Core/Component/MeshRenderer.hpp"
#include "Core/Component/ACollider.hpp"
#include "Game/Components/Item.hpp"
#include "Game/Components/Map.hpp"
#include "Game/Input.hpp"
#include "Game/Assets.hpp"

namespace Game
{
	namespace Component
	{
		Player						*Player::instance = nullptr;
        Player::Player(BeerEngine::GameObject *gameObject) :
			Component(gameObject),
			_transform(gameObject->transform),
			_gameStarted(false),
			_character(nullptr),
			noBombTimer(0)
		{
			instance = this;
		}

		Player::Player ( void ):
            _transform(BeerEngine::Transform::basic)
		{
			return ;
		}

		Player::Player ( Player const & src ):
            _transform(BeerEngine::Transform::basic)
		{
			*this = src;
			return ;
		}

		Player &	Player::operator=( Player const & rhs )
		{
			(void) rhs;
			if (this != &rhs)
			{}
			return (*this);
		}

		Player::~Player(void)
		{
			instance = nullptr;
		}

        void    Player::onDestroy(void)
        {
			_character->map->_player = nullptr;
        }

		void Player::startGame(void)
		{
			// std::cout << "start game from player" << std::endl;
			_gameStarted = true;
		}

		void    Player::start(void)
        {
			instance = this;
			play = false;
            _character = _gameObject->GetComponent<Game::Component::Character>();

			BeerEngine::Audio::AudioClip	*clip = Assets::GetAudioClip("assets/sounds/footsteps.wav");
			srcAudio->setBuffer(clip->getBuffer());
			srcAudio->setVolume(Game::Component::AudioManager::instance->getSoundVolume());

			BeerEngine::Audio::AudioClip	*itemClip = Assets::GetAudioClip("assets/sounds/item.wav");
			itemSrcAudio->setBuffer(itemClip->getBuffer());
			itemSrcAudio->setVolume(Game::Component::AudioManager::instance->getSoundVolume());
			// std::cout << "===============item volume =============" << Game::Component::AudioManager::instance->getSoundVolume() << std::endl;

			GameManager::GetInstance().onGameStart.bind(&Player::startGame, this);
        }

        void    Player::fixedUpdate(void)
        {

        }

        void    Player::update(void)
        {
			bool moving = false;
			_character->_direction = glm::vec2(0, 0);
			if (!_gameStarted)
				return;

			if (BeerEngine::Input::GetKey(Game::Input::keyBindings["move up"]))
            {
				moving = true;
				playStepSound();
				_character->move(Character::Direction::Up);
			}
            if (BeerEngine::Input::GetKey(Game::Input::keyBindings["move down"]))
			{
				moving = true;
				playStepSound();
                _character->move(Character::Direction::Down);
			}
            if (BeerEngine::Input::GetKey(Game::Input::keyBindings["move left"]))
            {
				moving = true;
				playStepSound();
				_character->move(Character::Direction::Left);
			}
            if (BeerEngine::Input::GetKey(Game::Input::keyBindings["move right"]))
            {
				moving = true;
				playStepSound();
				_character->move(Character::Direction::Right);
			}
			if (!moving)
				_character->stopMove();
            // if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::KP_0))
			// 	this->destroy();
            if (BeerEngine::Input::GetKeyDown(Game::Input::keyBindings["bomb"]))
			{
				// std::cout << "drop requested" << std::endl;
                _character->dropBomb();
			}
            // if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::KP_1))
            //     _gameObject->destroy(this);
			if (BeerEngine::Input::GetKeyUp(Game::Input::keyBindings["move up"]) &&
				BeerEngine::Input::GetKeyUp(Game::Input::keyBindings["move left"]) &&
				BeerEngine::Input::GetKeyUp(Game::Input::keyBindings["move down"]) &&
				BeerEngine::Input::GetKeyUp(Game::Input::keyBindings["move right"]))
			{
				srcAudio->setLooping(false);
				play = false;
			}
			if (noBombTimer != 0 && _character->_bombNb > 0)
				noBombTimer = 0;
			if (GameManager::GetInstance().storyMode && !_character->_bombNb
			&& Game::Component::Map::instance->hasBreakable() && !Game::Component::Map::instance->hasBlock(B))
				noBombTimer += BeerEngine::Time::GetDeltaTime();
			if (noBombTimer > 3)
				GameManager::GetInstance().setGameOver(glm::vec3(3, 2, 27), 8);
        }

        void            Player::renderUI(struct nk_context *ctx)
        {
			(void) ctx;
            // if (nk_begin(ctx, "Player", nk_rect(WINDOW_WIDTH - 330, 10, 320, 160), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_CLOSABLE))
            // {
            //     std::stringstream ss;
            //     ss << "Speed: " << _character->_speed;
            //     nk_layout_row_dynamic(ctx, 20, 1);
            //     nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
            //     ss.str(std::string());
            //     ss.clear();
            //     ss << "Bomb: " << _character->_bombNb;
            //     nk_layout_row_dynamic(ctx, 20, 1);
            //     nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
            //     ss.str(std::string());
            //     ss.clear();
            //     ss << "Size: " << _character->_explosionSize;
            //     nk_layout_row_dynamic(ctx, 20, 1);
            //     nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
            //     nk_layout_row_dynamic(ctx, 20, 1);
            //     nk_label(ctx, glm::to_string(_gameObject->transform.position).c_str(), NK_TEXT_LEFT);
            // }
            // nk_end(ctx);
        }

		void    Player::onColliderEnter(BeerEngine::Component::ACollider *other)
		{
			auto item = other->_gameObject->GetComponent<Game::Component::Item>();
			if (item)
			{
				if (item->_type != ItemType::Antidote || !_character->map->hasBreakable())
					this->itemSrcAudio->play();
			}
		}

        nlohmann::json	Player::serialize()
		{
			auto j = Component::serialize();
			j.merge_patch({
				{"componentClass", type},
				{"character", SERIALIZE_BY_ID(_character)},
				{"srcAudio", SERIALIZE_BY_ID(srcAudio)},
				{"itemSrcAudio", SERIALIZE_BY_ID(itemSrcAudio)},
			});
			return j;
		}

        void Player::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
    	{
			Component::deserialize(j, loader);
			DESERIALIZE_BY_ID(this->_character, Character, "character", loader);
			DESERIALIZE_BY_ID(this->srcAudio, BeerEngine::Audio::AudioSource, "srcAudio", loader);
			DESERIALIZE_BY_ID(this->itemSrcAudio, BeerEngine::Audio::AudioSource, "itemSrcAudio", loader);
		}

		void Player::playStepSound()
		{
			if (play == false)
			{
				play = true;
				srcAudio->setLooping(true);
				srcAudio->play();
			}
		}

		REGISTER_COMPONENT_CPP(Player)
    }
}
