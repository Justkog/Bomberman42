#include "Game/Components/Map.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/IO/FileUtils.hpp"

namespace Game
{
	namespace Component
	{

        Map::Map(BeerEngine::GameObject *gameObject) :
			Component(gameObject),
            _transform(gameObject->transform)
		{ }

        void    Map::start(void)
        {
			std::cout << "map start" << "\n";
			_player->createCrateSignal.bind(&Map::setDestruction, this);
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

        void    Map::mapUpdate(int x, int y)
        {
			_map[y][x] = 0;
        }

		void Map::setDestruction(float posX, float posY)
		{
			glm::vec2 Mpos = worldToMap(glm::vec3(posX, 0, posY));
			mapUpdate(static_cast<int>(Mpos.x), static_cast<int>(Mpos.y));
			// _map[static_cast<int>(Mpos.y)][static_cast<int>(Mpos.x)] = 0;

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
							addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY), true);
							break;
						case S:
							if (playerSpawn)
							{
								//addIA
							}
							else
							{
								_player->_gameObject->transform.position = glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY);
								// addPlayer(shader, glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY));
								playerSpawn = true;
							}
							break;
						case I:
							addItem(shader, glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY));

					}
				}
			}
		}
#include <sstream>
		void    Map::renderUI(struct nk_context *ctx)
		{
			if (nk_begin(ctx, "Map", nk_rect(10, 100, 320, 430), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_CLOSABLE))
            {
				nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, "position", NK_TEXT_LEFT);
				nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, glm::to_string(worldToMap(_player->_gameObject->transform.position)).c_str(), NK_TEXT_LEFT);
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

    }
}
