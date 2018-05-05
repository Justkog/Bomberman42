#include "Game/Components/IA.hpp"
#include "Game/Components/Character.hpp"
#include "Game/Components/Map.hpp"
#include "Core/GameObject.hpp"
#include "Core/Component/MeshRenderer.hpp"

//TEST
#include "Core/Input.hpp"
#include "Core/Window.hpp"
#include "Core/Physics/Physics.hpp"

namespace Game
{
	namespace Component
	{
        IA::IA(BeerEngine::GameObject *gameObject) :
			Component(gameObject),
            _transform(gameObject->transform),
            _hasObjective(false),
            _objective(0, 0)
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
            if (!_hasObjective)
            {
                //SEARCH TARGET
                _hasObjective = true;
                _objective = glm::vec2(3, 3);
            }
            if (_hasObjective)
            {
                if (moveToObjective())
                    _hasObjective = false;
            }
        }

        bool    IA::findPath(void)
        {
            std::vector<std::vector<int>> mapCopy;

            mapCopy.resize(map->_sizeY);
            for (int y = 0; y < map->_sizeY; ++y)
            {
                mapCopy[y].resize(map->_sizeX);
                for (int x = 0; x < map->_sizeX; ++x)
                    mapCopy[y][x] = map->_map[y][x];
            }
            return (false);
        }

        bool    IA::moveToObjective(void)
        {
            if (_path.empty() && map->worldToMap(_transform.position) != _objective)
            {
                findPath();
            }
            return (false);
        }

        void    IA::renderUI(struct nk_context *ctx)
        {
            if (nk_begin(ctx, "IA", nk_rect(WINDOW_WIDTH - 330, 500, 320, 160), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_CLOSABLE))
            {
                std::stringstream ss;
                ss << "Target: " << glm::to_string(_objective);
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                ss.str(std::string());
                // ss.clear();
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
