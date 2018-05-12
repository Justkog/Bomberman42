#include "Game/Components/IA.hpp"
#include "Game/Components/Character.hpp"
#include "Game/Components/Bomb.hpp"
#include "Game/Components/Map.hpp"
#include "Core/GameObject.hpp"
#include "Core/Component/MeshRenderer.hpp"

//TEST
#include "Core/Input.hpp"
#include "Core/Window.hpp"
#include "Core/Physics/Physics.hpp"
#include "Core/Component/RaysRenderer.hpp"

namespace Game
{
	namespace Component
	{
        IA::IA(BeerEngine::GameObject *gameObject) :
			Component(gameObject),
            _transform(gameObject->transform),
            _hasObjective(false),
            _pos(0, 0),
		    _type(ObjectiveType::MoveTo),
            _val(0)
		{
        }

        IA::~IA(void)
        {            
        }

        void    IA::onDestroy(void)
        {
            auto it = std::find(_character->map->_IAs.begin(), _character->map->_IAs.end(), this);

            if (it != _character->map->_IAs.end())
                _character->map->_IAs.erase(it);
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
                findObjective();
            if (_hasObjective)
            {
                if (moveToObjective())
                {
                    switch (_type)
                    {
                        case ObjectiveType::DropBomb:
                        case ObjectiveType::KillEnemy:
                            _character->dropBomb();
                        break;

                        case ObjectiveType::MoveTo:
                        break;

                        case ObjectiveType::TakeBonus:
                        break;
                    }
                    _hasObjective = false;
                }
            }
        }

        bool    IA::canMove(glm::vec3 dir)
        {
            std::vector<BeerEngine::Physics::RaycastHit> hits = BeerEngine::Physics::Physics::RaycastAllOrdered(_transform.position, dir);

            if (hits.size() > 1)
            {
                for (BeerEngine::Physics::RaycastHit hit : hits)
                {
                    auto character = hit.collider->_gameObject->GetComponent<Game::Component::Character>();
                    auto bomb = hit.collider->_gameObject->GetComponent<Game::Component::Bomb>();
                    auto myCol = _gameObject->GetComponent<BeerEngine::Component::ACollider>();
                    if ((character && character != _character) || (bomb && !hit.collider->hasException(myCol)))
                        return (false);
                }
            }
            return (true);
        }

        bool    IA::avoidExplosion(glm::vec3 pos, glm::vec3 dir, int offset)
        {
            std::vector<BeerEngine::Physics::RaycastHit> hits = BeerEngine::Physics::Physics::RaycastAllOrdered(pos, dir);
            Game::Component::Bomb *bomb;

            if (hits.size() > 0 + offset)
            {
                bomb = hits[0 + offset].collider->_gameObject->GetComponent<Game::Component::Bomb>();
                if (!bomb && hits[0 + offset].collider->_gameObject->GetComponent<Game::Component::IA>() == this && hits.size() > 1 + offset)
                    bomb = hits[1 + offset].collider->_gameObject->GetComponent<Game::Component::Bomb>();
                if (bomb && bomb->power >= std::abs(pos.z - bomb->_gameObject->transform.position.z) + std::abs(pos.x - bomb->_gameObject->transform.position.x))
                    return (false);
            }
            return (true);
        }

        bool    IA::avoidAllExplosions(glm::vec2 pos, int offset)
        {
            if (!avoidExplosion(map->mapToWorld(pos), glm::vec3(50, 0, 0), offset)
            || !avoidExplosion(map->mapToWorld(pos), glm::vec3(-50, 0, 0), offset)
            || !avoidExplosion(map->mapToWorld(pos), glm::vec3(0, 0, 50), offset)
            || !avoidExplosion(map->mapToWorld(pos), glm::vec3(0, 0, -50), offset))
                return (false);
            return (true);
        }

        int     IA::checkExplosionRay(glm::vec3 pos, glm::vec3 dir, ObjectiveType &type)
        {
            BeerEngine::Physics::RaycastHit hit;
            int val = 0;

            if (BeerEngine::Physics::Physics::Raycast(pos, dir, hit, 0))
            {
                auto breakable = hit.collider->_gameObject->GetComponent<Game::Component::Breakable>();
                auto character = hit.collider->_gameObject->GetComponent<Game::Component::Character>();
                auto item = hit.collider->_gameObject->GetComponent<Game::Component::Item>();

                if (breakable && !character && !avoidAllExplosions(map->worldToMap(hit.collider->_gameObject->transform.position), 1))
                    val -= 6;
                if (breakable && hit.collider->_gameObject != _gameObject)
                {
                    val += 6;
                    type = ObjectiveType::DropBomb;
                }
                if (character && hit.collider->_gameObject != _gameObject)
                {
                    val += 12;
                    type = ObjectiveType::KillEnemy;
                }
                if (item)
                    val -= 15;
            }
            return (val);
        }

        int     IA::checkExplosionZone(glm::vec2 pos, ObjectiveType &type)
        {
            BeerEngine::Physics::RaycastHit hit;
            int val = 0;

            val += checkExplosionRay(map->mapToWorld(pos), glm::vec3(_character->_explosionSize, 0, 0), type);
            val += checkExplosionRay(map->mapToWorld(pos), glm::vec3(-_character->_explosionSize, 0, 0), type);
            val += checkExplosionRay(map->mapToWorld(pos), glm::vec3(0, 0, _character->_explosionSize), type);
            val += checkExplosionRay(map->mapToWorld(pos), glm::vec3(0, 0, -_character->_explosionSize), type);
            return (val);
        }

        int    IA::findObjective(bool save)
        {
            ObjectiveType objective = ObjectiveType::MoveTo;
            std::vector<glm::vec2> path;
			glm::vec2 target(0);
            glm::vec2 mapPos(map->worldToMap(_gameObject->transform.position));
            int val = avoidAllExplosions(mapPos) ? 0 : -1000;

            for (int y = 0; y < map->_sizeY; ++y)
            {
                for (int x = 0; x < map->_sizeX; ++x)
                {
                    int tmpVal = 0;
                    ObjectiveType tmpObj = ObjectiveType::MoveTo;

                    if (map->canWalk(glm::vec2(x, y)) && avoidAllExplosions(glm::vec2(x, y)))
                    {
                        if (map->_map[y][x] == 9)
                        {
                            tmpVal += 15;
                            tmpObj = ObjectiveType::TakeBonus;
                        }
                        else if (_character->_bombNb > 0)
                            tmpVal += checkExplosionZone(glm::vec2(x, y), tmpObj);
                        if (tmpVal > val - (std::abs(mapPos.x - target.x) + std::abs(mapPos.y - target.y)) && !findPath(glm::vec2(x, y), &path))
                            continue;
                        tmpVal -= path.size();
                        if (tmpVal > val)
                        {
                            target = glm::vec2(x, y);
                            objective = tmpObj;
                            val = tmpVal;
                        }
                        else
                            path.clear();
                    }
                }
            }
            if (target == glm::vec2(0))
                return (-1000);
            if (save)
            {
                _pos = target;
                _type = objective;
                _hasObjective = true;
                _path = path;
                _val = val;
            }
            return (val);
        }

        bool    IA::moveToObjective(void)
        {
            if (glm::distance2(map->mapToWorld(_pos), _transform.position) < 0.001)
                return (true);
            if (_path.empty())
            {
                if (!findPath(_pos, &_path))
                    _hasObjective = false;
            }
            else if (map->worldToMap(_transform.position) != _pos && !findPath(_pos))
            {
                _path.clear();
                _hasObjective = false;
            }
            if (!_path.empty() && !moveToNextCell())
            {
                _path.clear();
                _hasObjective = false;
            }
            return (false);
        }

        bool    IA::moveToNextCell(void)
        {
            glm::vec3 dir;

            if (!avoidAllExplosions(_path[0]) && avoidAllExplosions(map->worldToMap(_transform.position)))
                return (true);
            if (glm::distance2(map->mapToWorld(_path[0]), _transform.position) < 0.001)
            {
                _val++;
                _path.erase(_path.begin());
                if (_type == ObjectiveType::KillEnemy)
                    return (false);
            }
            dir = map->mapToWorld(_path[0]) - _transform.position;
            if (!canMove(dir))
                return (false);
            if (std::abs(dir.z) <= 0.015)
                _transform.position.z = map->mapToWorld(_path[0]).z;
            else if (dir.z > 0.015)
                    _character->move(Character::Direction::Up);
            else if (dir.z < -0.015)
                    _character->move(Character::Direction::Down);
            if (std::abs(dir.x) <= 0.015)
                _transform.position.x = map->mapToWorld(_path[0]).x;
            else if (dir.x > 0.015)
                    _character->move(Character::Direction::Left);
            else if (dir.x < -0.015)
                    _character->move(Character::Direction::Right);
            return (true);
        }






            ///////////////////////////////////////////////////////////////////////////////////////
           ///////////////////////////////////////////////////////////////////////////////////////
          //------------------------------------ PATHFINDER -----------------------------------//
         ///////////////////////////////////////////////////////////////////////////////////////
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

        bool    IA::analyzeMap(glm::vec2 start, std::vector<std::vector<int>> &mapCopy, glm::vec2 target)
        {
            std::queue<glm::vec2> toCheck;
            glm::vec2 cur;
            int weight;

            mapCopy[target.y][target.x] = 1000;
            toCheck.push(target);
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

        bool    IA::findPath(glm::vec2 target, std::vector<glm::vec2> *path)
        {
            std::vector<std::vector<int>> mapCopy;
            glm::vec2 start = map->worldToMap(_transform.position);

            mapCopy.resize(map->_sizeY);
            for (int y = 0; y < map->_sizeY; ++y)
            {
                mapCopy[y].resize(map->_sizeX);
                for (int x = 0; x < map->_sizeX; ++x)
                {
                    if (!map->canWalk(glm::vec2(x, y)) && start != glm::vec2(x, y))
                        mapCopy[y][x] = -1;
                    else
                        mapCopy[y][x] = 0;
                    if (map->_map[y][x] == B && start == glm::vec2(x, y))
                        mapCopy[y][x] = 0;
                }
            }
            if (analyzeMap(start, mapCopy, target))
            {
                if (path)
                {
                    for (glm::vec2 cur(start); cur != target;)
                    {
                        cur = getPath(cur, mapCopy);
                        path->push_back(cur);
                    }
                }
                return (true);
            }
            return (false);
        }
            ///////////////////////////////////////////////////////////////////////////////////////////
           ///////////////////////////////////////////////////////////////////////////////////////////
          //------------------------------------ END PATHFINDER -----------------------------------//
         ///////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////






        void    IA::renderUI(struct nk_context *ctx)
        {
            std::stringstream winName;
            winName << "IA " << this;
            if (nk_begin(ctx, winName.str().c_str(), nk_rect(WINDOW_WIDTH - 330, 500, 320, 160), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_CLOSABLE))
            {
                std::stringstream ss;
                ss << "Target: " << glm::to_string(_pos);
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                ss.str(std::string());
                ss.clear();
                ss << "Val: " << _val;
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                ss.str(std::string());
                ss.clear();
                ss << "hasObjective: " << (_hasObjective ? "true" : "false");
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                ss.str(std::string());
                ss.clear();
                ss << "Objective: ";
                switch (_type)
                {
                    case ObjectiveType::DropBomb:
                        ss << "DropBomb";
                    break;

                    case ObjectiveType::MoveTo:
                        ss << "MoveTo";
                    break;

                    case ObjectiveType::TakeBonus:
                        ss << "TakeBonus";
                    break;

                    case ObjectiveType::KillEnemy:
                        ss << "KillEnemy";
                    break;
                }
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                ss.str(std::string());
                ss.clear();
                if (_path.size() > 0)
                {
                    ss << "Next: " << glm::to_string(_path[0]);
                    nk_layout_row_dynamic(ctx, 20, 1);
                    nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                    ss.str(std::string());
                    ss.clear();
                }
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
