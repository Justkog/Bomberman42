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
                _objective = glm::vec2(1, 1);
            }
            if (_hasObjective)
            {
                if (moveToObjective())
                    _hasObjective = false;
            }
        }

        bool    IA::moveToObjective(void)
        {
            if (_path.empty() && glm::distance2(map->mapToWorld(_objective), _transform.position) > 0.01)
            {
                if (findPath())
                {
                    //PATH FIND WOUHOU
                }
                else
                {
                    //DO SOMETHING ELSE
                }
            }
            else if (glm::distance2(map->mapToWorld(_objective), _transform.position) < 0.01)
            {
                return (true);
            }
            else
            {
                moveToNextCell();
            }
            return (false);
        }

        void    IA::moveToNextCell(void)
        {
            // glm::vec2 dir;

            if (glm::distance2(map->mapToWorld(_path[0]), _transform.position) < 0.01)
                _path.erase(_path.begin());
            dir = map->mapToWorld(_path[0]) - _transform.position;
            if (dir.z > 0)
                    _character->move(Character::Direction::Up);
            else if (dir.z < 0)
                    _character->move(Character::Direction::Down);
            if (dir.x > 0)
                    _character->move(Character::Direction::Left);
            else if (dir.x < 0)
                    _character->move(Character::Direction::Right);
        }

          ///////////////////////////////////////////////////////////////////////////////////////
         //------------------------------------ PATHFINDER -----------------------------------//
        ///////////////////////////////////////////////////////////////////////////////////////
        bool	IA::checkCell(glm::vec2 cur, std::vector<std::vector<int>> &mapCopy, int weight, std::queue<glm::vec2> &toCheck, glm::vec2 start)
        {
            if (cur.y >= 0 && cur.x >= 0 && cur.y < map->_sizeY && cur.x < map->_sizeX
            && (!mapCopy[cur.y][cur.x] || (mapCopy[cur.y][cur.x] >= 1000 && mapCopy[cur.y][cur.x] > weight)))
            {
                if (glm::vec2(cur.x, cur.y) == start)
                    return (true);
                mapCopy[cur.y][cur.x] = weight + 1;
                toCheck.push(glm::vec2(cur.x, cur.y));
            }
            return (false);
        }

        bool    IA::analyzeMap(glm::vec2 start, std::vector<std::vector<int>> &mapCopy)
        {
            std::queue<glm::vec2> toCheck;
            glm::vec2 cur;
            int weight;

            mapCopy[_objective.y][_objective.x] = 1000;
            toCheck.push(_objective);
            while (!toCheck.empty())
            {
                cur = toCheck.front();
                weight = mapCopy[cur.y][cur.x];
                if (checkCell(glm::vec2(cur.x, cur.y - 1), mapCopy, weight, toCheck, start)
                || checkCell(glm::vec2(cur.x, cur.y + 1), mapCopy, weight, toCheck, start)
                || checkCell(glm::vec2(cur.x + 1, cur.y), mapCopy, weight, toCheck, start)
                || checkCell(glm::vec2(cur.x - 1, cur.y), mapCopy, weight, toCheck, start))
                    return (true);
                toCheck.pop();
            }
            return (false);
        }

        glm::vec2    IA::getPath(glm::vec2 cur, std::vector<std::vector<int>> &mapCopy)
        {
            int weight = !mapCopy[cur.y][cur.x] ? 100000 : mapCopy[cur.y][cur.x];
            glm::vec2 next;
            glm::vec2 path = cur;

            next = glm::vec2(cur.x + 1, cur.y);
            if (next.y >= 0 && next.x >= 0 && next.y < map->_sizeY && next.x < map->_sizeX
            && mapCopy[next.y][next.x] >= 1000 && mapCopy[next.y][next.x] < weight)
            {
                weight = mapCopy[next.y][next.x];
                path = next;
            }
            next = glm::vec2(cur.x - 1, cur.y);
            if (next.y >= 0 && next.x >= 0 && next.y < map->_sizeY && next.x < map->_sizeX
            && mapCopy[next.y][next.x] >= 1000 && mapCopy[next.y][next.x] < weight)
            {
                weight = mapCopy[next.y][next.x];
                path = next;
            }
            next = glm::vec2(cur.x, cur.y - 1);
            if (next.y >= 0 && next.x >= 0 && next.y < map->_sizeY && next.x < map->_sizeX
            && mapCopy[next.y][next.x] >= 1000 && mapCopy[next.y][next.x] < weight)
            {
                weight = mapCopy[next.y][next.x];
                path = next;
            }
            next = glm::vec2(cur.x, cur.y + 1);
            if (next.y >= 0 && next.x >= 0 && next.y < map->_sizeY && next.x < map->_sizeX
            && mapCopy[next.y][next.x] >= 1000 && mapCopy[next.y][next.x] < weight)
            {
                weight = mapCopy[next.y][next.x];
                path = next;
            }
            return (path);
        }

        bool    IA::findPath(void)
        {
            std::vector<std::vector<int>> mapCopy;
            glm::vec2 start = map->worldToMap(_transform.position);

            mapCopy.resize(map->_sizeY);
            for (int y = 0; y < map->_sizeY; ++y)
            {
                mapCopy[y].resize(map->_sizeX);
                for (int x = 0; x < map->_sizeX; ++x)
                {
                    if (map->_map[y][x] == 1 || map->_map[y][x] == 2)
                        mapCopy[y][x] = -1;
                    else
                        mapCopy[y][x] = 0;
                }
            }
            if (analyzeMap(start, mapCopy))
            {
                for (glm::vec2 cur(start); cur != _objective;)
                {
                    cur = getPath(cur, mapCopy);
                    _path.push_back(cur);
                }
                return (true);
            }
            return (false);
        }
          ///////////////////////////////////////////////////////////////////////////////////////////
         //------------------------------------ END PATHFINDER -----------------------------------//
        ///////////////////////////////////////////////////////////////////////////////////////////

        void    IA::renderUI(struct nk_context *ctx)
        {
            if (nk_begin(ctx, "IA", nk_rect(WINDOW_WIDTH - 330, 500, 320, 160), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_CLOSABLE))
            {
                std::stringstream ss;
                ss << "Target: " << glm::to_string(_objective);
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                ss.str(std::string());
                ss.clear();
                ss << "Dir: " << glm::to_string(dir);
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                ss.str(std::string());
                ss.clear();
                ss << "Next: " << glm::to_string(_path[0]);
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                ss.str(std::string());
                ss.clear();
                ss << "hasObjective: " << (_hasObjective ? "true" : "false");
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                ss.str(std::string());
                ss.clear();
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
