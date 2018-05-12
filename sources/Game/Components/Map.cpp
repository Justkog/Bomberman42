#include "Game/Components/Map.hpp"
// #include "Game/Components/Breakable.hpp"

#include "Core/Component/BoxCollider2D.hpp"
#include <sstream>
#include "Core/IO/FileUtils.hpp"
#include "Core/Audio/AudioSource.hpp"
#include "Game/Game.hpp"

namespace Game
{
	namespace Component
	{

        Map::Map(BeerEngine::GameObject *gameObject) :
			Component(gameObject),
            _transform(gameObject->transform)
		{ }

		Map::~Map()
		{
			for (int y = 0; y < _sizeY; y++)
			{
				delete[] _map[y];
			}
			delete[]_map;
		}

        void    Map::start(void)
        {
			// std::cout << "map start" << "\n";
			// _player->createCrateSignal.bind(&Map::mapUpdate, this);
		}

		BeerEngine::GameObject *Map::createCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, BeerEngine::Component::RBType kinematic)
		{
			auto mapBlocGO = _gameObject->_scene.instantiate<BeerEngine::GameObject>("Prefabs/mapCrate.prefab");
			mapBlocGO->transform.position = pos;
			mapBlocGO->transform.scale = scale;
			return (mapBlocGO);
		}

		BeerEngine::GameObject *Map::addItem(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 pos)
		{
			std::cout << "item start" << std::endl;
			auto itemGO = addCrate<BeerEngine::Component::CircleCollider>(shader, glm::vec3(0.5, 0.5, 0.5), pos, BeerEngine::Component::RBType::Kinematic);
			itemGO->name = "item";
			// auto as = itemGO->AddComponent<BeerEngine::Audio::AudioSource>();
			auto item = itemGO->AddComponent<Game::Component::Item>();
			itemGO->AddComponent<Game::Component::Breakable>();
			item->map = this;
			// item->as = as;
			auto itemColl = itemGO->GetComponent<BeerEngine::Component::CircleCollider>();
			itemColl->_isTrigger = true;
			return itemGO;
		}

		BeerEngine::GameObject *Map::createItem(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 pos)
		{
			auto mapBlocGO = _gameObject->_scene.instantiate<BeerEngine::GameObject>("Prefabs/item.prefab");
			mapBlocGO->transform.position = pos;
			// mapBlocGO->transform.scale = glm::vec3(0.5, 0.5, 0.5);
			return (mapBlocGO);
		}

		void	Map::setMap(std::vector<std::vector<int>>map, size_t sizeX, size_t sizeY)
		{
			_sizeX = sizeX;
			_sizeY = sizeY;
				_map = new int*[sizeY];
				for (int y = 0; y < sizeY; y++)
				{
					_map[y] = new int[sizeX];
					for (int x = 0; x < sizeX; x++)
						_map[y][x] = map[y][x];
				}
		}

		void	Map::setRandomMap(std::vector<std::vector<int>>map, size_t sizeX, size_t sizeY)
		{
			_sizeX = sizeX;
			_sizeY = sizeY;

				_map = new int*[sizeY];
				for (int y = 0; y < sizeY; y++)
				{
					_map[y] = new int[sizeX];
					for (int x = 0; x < sizeX; x++)
					{
						if (map[y][x] == 0)
						{
							if ((rand() % 2 + 1) == 2)
								map[y][x] = 2;
						// 	// else
						// 	// 	_map[y][x] = 0;
						// 	// std::cout << y*10+x << std::endl;
						}
						// else
							_map[y][x] = map[y][x];
						// std::cout << y << " " << x << " = " << _map[y][x] << std::endl;
					}
				}
		}

        void    Map::mapUpdate(int x, int y, int value)
        {
			_map[y][x] = value;
        }

		void Map::mapUpdate(glm::vec3 pos, int value)
		{
			glm::vec2 Mpos = worldToMap(glm::vec3(pos.x, 0, pos.z));
			mapUpdate(static_cast<int>(Mpos.x), static_cast<int>(Mpos.y), value);
		}

		void	Map::drawMap(BeerEngine::Graphics::ShaderProgram *shader)
		{
			int type = 0;
			bool playerSpawn = false;

			for (int row = 0; row < _sizeY; row++)
			{
				for (int col = 0; col < _sizeX; col++)
				{
					type = _map[row][col];
					switch (type)
					{
						case 1:
							addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY), BeerEngine::Component::RBType::Kinematic);
							// createCrate(shader, glm::vec3(1, 1, 1), glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY), BeerEngine::Component::RBType::Kinematic);
							break;
						case 2:
							addDestoyableCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY), BeerEngine::Component::RBType::Kinematic);
							break;
						case S:
							if (playerSpawn)
							{
								// _IA->_gameObject->transform.position = glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY);
							}
							else
							{
								_player->_gameObject->transform.position = glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY);
								playerSpawn = true;
							}
							break;
						case I:
							addItem(shader, glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY));
							// createItem(shader, glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY));

					}
				}
			}
		}

		void    Map::renderUI(struct nk_context *ctx)
		{
			if (nk_begin(ctx, "Map", nk_rect(10, 100, 220, 430), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_CLOSABLE))
            {
				nk_layout_row_dynamic(ctx, 20, 1);
				// if (_player)
				// {
	            //     nk_label(ctx, "position", NK_TEXT_LEFT);
				// 	nk_layout_row_dynamic(ctx, 20, 1);
	            //     nk_label(ctx, glm::to_string(worldToMap(_player->_gameObject->transform.position)).c_str(), NK_TEXT_LEFT);
				// }
				nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, "map", NK_TEXT_LEFT);
				for (int row = 0; row < _sizeY; row++)
				{
					std::stringstream ss;
					for (int col = 0; col < _sizeX; col++)
						ss << _map[row][col];
					nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);

				}
            }
            nk_end(ctx);
		}

		glm::vec2		Map::worldToMap(glm::vec3 pos)
		{
			return glm::vec2(round((pos.x - (_sizeX / 2)) * (-1)), round(_sizeY - pos.z));
		}

		bool			Map::canWalk(glm::vec2 pos)
		{
			int x = static_cast<int>(pos.x);
			int y = static_cast<int>(pos.y);
			if (_map[y][x] == 0 || _map[y][x] == -1 || _map[y][x] == 9)
				return true;
			return false;
		}

		nlohmann::json	Map::serialize()
		{
			return {
				{"componentClass", type},
			};
		}

		void Map::deserialize(const nlohmann::json & j)
		{

		}

		REGISTER_COMPONENT_CPP(Map)

		glm::vec3		Map::mapToWorld(glm::vec2 pos, float y)
		{
			return glm::vec3(-pos.x + (_sizeX / 2), y, -pos.y + _sizeY);
		}
    }
}
