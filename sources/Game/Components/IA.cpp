#include "Game/Components/IA.hpp"
#include "Game/Components/Character.hpp"
#include "Core/GameObject.hpp"
#include "Core/Component/MeshRenderer.hpp"

namespace Game
{
	namespace Component
	{
        IA::IA(BeerEngine::GameObject *gameObject) :
			Component(gameObject),
            _transform(gameObject->transform)
		{

        }

        void    IA::start(void)
        {
            _character = _gameObject->GetComponent<Game::Component::Character>();
        }

        void    IA::fixedUpdate(void)
        {

        }

        void    IA::update(void)
        {
            // //MOVE UP
            // _character->move(Character::Direction::Up);
            // //MOVE DOWN
            // _character->move(Character::Direction::Down);
            // //MOVE LEFT
            // _character->move(Character::Direction::Left);
            // //MOVE RIGHT
            // _character->move(Character::Direction::Right);
            // //MOVE BOMB
            // _character->dropBomb();
        }

        void            IA::renderUI(struct nk_context *ctx)
        {
            if (nk_begin(ctx, "IA", nk_rect(WINDOW_WIDTH - 330, 10, 320, 160), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_CLOSABLE))
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

        nlohmann::json	IA::serialize()
		{
			return nlohmann::json {
				{"componentClass", typeid(IA).name()},
			};
		}

        void IA::deserialize(const nlohmann::json & j)
    	{

		}

		REGISTER_COMPONENT_CPP(IA)
    }
}
