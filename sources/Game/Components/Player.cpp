#include "Game/Components/Player.hpp"
#include "Game/Components/Character.hpp"
#include "Core/Input.hpp"
#include "Core/GameObject.hpp"
#include "Core/Component/MeshRenderer.hpp"

namespace Game
{
	namespace Component
	{
        Player::Player(BeerEngine::GameObject *gameObject) :
			Component(gameObject),
            _transform(gameObject->transform)
		{ }

        void    Player::start(void)
        {
			play = false;
            _character = _gameObject->GetComponent<Game::Component::Character>();
			BeerEngine::Audio::AudioClip   		clip("assets/sounds/footsteps.wav");
			srcAudio.setBuffer(clip.getBuffer());
			srcAudio.setLooping(false);
        }

        void    Player::fixedUpdate(void)
        {

        }

        void    Player::update(void)
        {
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_8))
            {
				if (play == false)
				{
					play = true;
					srcAudio.setLooping(true);
					srcAudio.play();
				}
				_character->move(Character::Direction::Up);
			}
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_5))
			{
				if (play == false)
				{
					play = true;
					srcAudio.setLooping(true);
					srcAudio.play();
				}
                _character->move(Character::Direction::Down);
			}
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_4))
            {
				if (play == false)
				{
					play = true;
					srcAudio.setLooping(true);
					srcAudio.play();
				}
				_character->move(Character::Direction::Left);
			}
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_6))
            {
				if (play == false)
				{
					play = true;
					srcAudio.setLooping(true);
					srcAudio.play();
				}
				_character->move(Character::Direction::Right);
			}
            if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::KP_0))
				this->destroy();
            if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::KP_2))
                _character->dropBomb();
            if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::KP_1))
                _gameObject->destroy(this);
			if (BeerEngine::Input::GetKeyUp(BeerEngine::KeyCode::KP_8) &&
				BeerEngine::Input::GetKeyUp(BeerEngine::KeyCode::KP_4) &&
				BeerEngine::Input::GetKeyUp(BeerEngine::KeyCode::KP_5) &&
				BeerEngine::Input::GetKeyUp(BeerEngine::KeyCode::KP_6))
			{
				srcAudio.setLooping(false);
				play = false;
			}

        }

        void            Player::renderUI(struct nk_context *ctx)
        {
            if (nk_begin(ctx, "Player", nk_rect(WINDOW_WIDTH - 330, 10, 320, 160), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_CLOSABLE))
            {
                std::stringstream ss;
                ss << "Speed: " << _character->_speed;
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                ss.str(std::string());
                ss.clear();
                ss << "Bomb: " << _character->_bombNb;
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                ss.str(std::string());
                ss.clear();
                ss << "Size: " << _character->_explosionSize;
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, glm::to_string(_gameObject->transform.position).c_str(), NK_TEXT_LEFT);
            }
            nk_end(ctx);
        }

        nlohmann::json	Player::serialize()
		{
			return nlohmann::json {
				{"componentClass", typeid(Player).name()},
			};
		}

        void Player::deserialize(const nlohmann::json & j)
    	{

		}

		REGISTER_COMPONENT_CPP(Player)
    }
}
