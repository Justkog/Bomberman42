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

        void    Map::update(void)
        {

        }

		void Map::setDestruction(float posX, float posY)
		{
			std::cout << "setting destr!" << "\n";
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
