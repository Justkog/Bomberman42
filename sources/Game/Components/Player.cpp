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
		{

        }

        void    Player::start(void)
        {
            _character = _gameObject->GetComponent<Game::Component::Character>();
        }

        void    Player::fixedUpdate(void)
        {

        }

        void    Player::update(void)
        {
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::I))
                    _character->move(Character::Direction::Up);
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::K))
                    _character->move(Character::Direction::Down);
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::J))
                    _character->move(Character::Direction::Left);
            if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::L))
                    _character->move(Character::Direction::Right);
            if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::B))
            {
                createCrateSignal.emit(_gameObject->transform.position.x, _gameObject->transform.position.z);
                std::cout << "emitting" << "\n";
            }
            if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::KP_0))
				this->destroy();
            if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::O))
                _character->dropBomb();
            if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::KP_1))
                _gameObject->destroy(this);
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
