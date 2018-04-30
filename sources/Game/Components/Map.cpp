#include "Game/Components/Map.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/IO/FileUtils.hpp"

namespace Game
{
	namespace Component
	{
		int	lvl1[ROW][COL] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,S,0,0,0,0,0,0,0,0,0,0,0,0,0,S,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,I,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
			{1,S,0,0,0,0,0,0,0,0,0,0,0,0,0,S,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

        Map::Map(BeerEngine::GameObject *gameObject) :
			Component(gameObject),
            _transform(gameObject->transform)
		{
			loadMap(lvl1);
        }

        void    Map::start(void)
        {
			// drawMap();
		}

        void    Map::loadMap(int arr[ROW][COL])
        {
			for (int row = 0; row < ROW; row++)
			{
				for (int col = 0; col < COL; col++)
					_map[row][col] = arr[row][col];
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
					// addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(col * 2, 0.5, row * 2), true);
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
    }
}
