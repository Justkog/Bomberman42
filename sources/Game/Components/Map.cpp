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
		{
			// setMap(tab, 17, 13);
			// loadMap(lvl1);
        }

        void    Map::start(void)
        {
			// drawMap();
		}

		void	Map::setMap(std::vector<std::vector<int>>map, size_t sizeX, size_t sizeY)
		{
				_map = new int*[sizeY];
				for (int y = 0; y < sizeY; y++)
				{
					_map[y] = new int[sizeX];
					for (int x = 0; x < sizeX; x++)
						_map[y][x] = map[y][x];
				}
		}

        void    Map::update(void)
        {

        }

		void	Map::drawMap(BeerEngine::Graphics::ShaderProgram *shader)
		{
			int type = 0;
			bool playerSpawn = false;

			for (int row = 0; row < ROW; row++)
			{
				for (int col = 0; col < COL; col++)
				{
					type = _map[row][col];
					switch (type)
					{
						case 1:
							addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-col + (COL / 2), 0.5, -row + ROW), true);
							break;
						case S:
							if (playerSpawn)
							{
								//addIA
							}
							else
							{
								addPlayer(shader, glm::vec3(-col + (COL / 2), 0.5, -row + ROW));
								playerSpawn = true;
							}
							break;
						case I:
							addItem(shader, glm::vec3(-col + (COL / 2), 0.5, -row + ROW));

					}
				}
			}
		}
		void    Map::renderUI(struct nk_context *ctx)
		{
			if (nk_begin(ctx, "Map", nk_rect(10, 270, 320, 160), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_CLOSABLE))
            {
				nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, "Hello World!", NK_TEXT_LEFT);
            }
            nk_end(ctx);
		}
    }
}
