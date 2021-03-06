#include "Game/Components/Map.hpp"
#include "Game/Components/IA.hpp"
#include "Game/Components/Character.hpp"
// #include "Game/Components/Breakable.hpp"

#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Component/ParticleBase.hpp"
#include "Core/GameObject.hpp"
#include "Core/Mathf.hpp"
#include <sstream>
#include "Core/IO/FileUtils.hpp"
#include "Core/Audio/AudioSource.hpp"
#include "Core/Json/Json.hpp"
#include "Game/Components/Bomb.hpp"
#include "Game/Components/GameManager.hpp"
#include "Core/Component/ModelRenderer.hpp"

namespace Game
{
	namespace Component
	{

		Map		*Map::instance = nullptr;
        Map::Map(BeerEngine::GameObject *gameObject) :
			Component(gameObject),
            _transform(gameObject->transform)
		{
			instance = this;
		}

		Map::Map ( void ):
            _transform(BeerEngine::Transform::basic)
		{
			return ;
		}

		Map::Map ( Map const & src ):
            _transform(BeerEngine::Transform::basic)
		{
			*this = src;
			return ;
		}

		Map &				Map::operator=( Map const & rhs )
		{
			(void) rhs;
			if (this != &rhs)
			{}
			return (*this);
		}

		Map::~Map()
		{
			instance = nullptr;
			for (int y = 0; y < _sizeY; y++)
			{
				delete[] _map[y];
			}
			delete[] _map;
		}

        void    Map::start(void)
        {
			instance = this;
			// std::cout << "map start" << "\n";
			Game::Component::Bomb::explosionTexture = Assets::GetTexture("assets/textures/ParticleAtlas.png");
			// itemSpeedBoostTex = Assets::GetTexture("assets/models/Shoes/botafinal2-TM_u0_v0.png");
			// itemBombTex = Assets::GetTexture("assets/models/Bomb/bombbody_BaseColor.png");
			itemRangeTex = Assets::GetTexture("assets/textures/fire_color.png");
			itemSpeedBoostTex = Assets::GetTexture("assets/models/Shoes/botafinal2-TM_u0_v0_small.png");
			itemBombTex = Assets::GetTexture("assets/textures/Bomb/bomb_color.png");
			// itemRangeTex = Assets::GetTexture("assets/textures/button_active.png");
			itemSpeedBoostMesh = Assets::GetModel("assets/models/Shoes/Shoes.obj");
			itemBombMesh = Assets::GetModel("assets/models/Bomb/modified_bomb.obj");
			itemRangeMesh = Assets::GetModel("assets/models/Fire/fire.obj");
			drawMap();
			uiInit = true;
		}

		BeerEngine::GameObject *Map::createCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, BeerEngine::Component::RBType kinematic)
		{
			(void) shader;
			(void) kinematic;
			auto mapBlocGO = _gameObject->_scene.instantiate<BeerEngine::GameObject>("assets/Prefabs/mapCrate.prefab");
			mapBlocGO->transform.position = pos;
			mapBlocGO->transform.scale = scale;
			return (mapBlocGO);
		}

		BeerEngine::GameObject *Map::addItem(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 pos, int type)
		{
			(void) shader;
			// std::cout << "item start" << std::endl;
			BeerEngine::Component::MeshRenderer *meshRenderer;
			auto itemGO = _gameObject->_scene.instantiate<BeerEngine::GameObject>();
			itemGO->name = "item";
			itemGO->transform.position = pos;
			itemGO->immortalTimer = 1.5f;
			if (type != ItemType::AntidoteDeco && type != ItemType::FireDeco)
			{
				auto itemColl = itemGO->AddComponent<BeerEngine::Component::CircleCollider>();
				itemColl->_isTrigger = true;
				itemColl->_radius = 0.3;
			}
			auto item = itemGO->AddComponent<Game::Component::Item>();
			item->map = this;
			if (type == -1)
				item->_type = static_cast<Game::Component::ItemType>(glm::linearRand(0, static_cast<int>(ItemType::ExplosionBoost)));
			else
				item->_type = static_cast<Game::Component::ItemType>(type);
			if (item->_type != ItemType::Antidote)
				itemGO->AddComponent<Game::Component::Breakable>();
			if (type != ItemType::FireDeco)
			{
				meshRenderer = itemGO->AddComponent<BeerEngine::Component::MeshRenderer>();
				BeerEngine::Graphics::Texture *itemTex = nullptr;
				BeerEngine::Graphics::AMaterial *itemMat = new BeerEngine::Graphics::AMaterial(BeerEngine::Graphics::Graphics::defaultShader);
				switch (item->_type)
				{
					case ItemType::SpeedBoost:
						meshRenderer->setMesh(itemSpeedBoostMesh);
						itemTex = itemSpeedBoostTex;
						itemGO->transform.scale = glm::vec3(0.3, 0.3, 0.3);
						break;
					case ItemType::AddBomb:
						meshRenderer->setMesh(itemBombMesh);
						itemTex = itemBombTex;
						itemGO->transform.scale = glm::vec3(0.1, 0.1, 0.1);
						break;
					case ItemType::ExplosionBoost:
						meshRenderer->setMesh(itemRangeMesh);
						itemTex = itemRangeTex;
						itemGO->transform.scale = glm::vec3(1, 1, 1);
						break;
					case ItemType::AntidoteDeco:
					case ItemType::Antidote:
						meshRenderer->setMesh(itemBombMesh);
						itemTex = itemRangeTex;
						itemGO->transform.scale = glm::vec3(0.2, 0.2, 0.2);
						break;
					case ItemType::FireDeco:
						break;
				}
				itemMat->setAlbedo(itemTex);
				meshRenderer->setMaterial(itemMat);
			}
			else
			{
				auto particle = itemGO->AddComponent<BeerEngine::Component::ParticleBase>();
				particle->setTexture(Assets::GetTexture("assets/textures/ParticleAtlas.png"));
				particle->setColor(glm::vec4(1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
				particle->setAnimate(true, 64, 8, 8);
				particle->setLifeTime(3.0f);
				particle->setSize(2.0f, 1.0f);
				particle->setSpawnTime(1.0f / 60.0f);
				particle->setVelocity(glm::vec3(0, 1, 0));
				glm::vec4 c1(BeerEngine::Mathf::Range(0.25f, 1.0f), BeerEngine::Mathf::Range(0.25f, 1.0f), BeerEngine::Mathf::Range(0.25f, 1.0f), 1.0f);
				glm::vec4 c2(BeerEngine::Mathf::Range(0.25f, 1.0f), BeerEngine::Mathf::Range(0.25f, 1.0f), BeerEngine::Mathf::Range(0.25f, 1.0f), 1.0f);
				particle->setColor(c1, c2);
				particle->offset = glm::vec3(0, 0, 0.25f);
			}
			
			return (itemGO);
		}

		BeerEngine::GameObject *Map::createItem(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 pos)
		{
			(void) shader;
			auto mapBlocGO = _gameObject->_scene.instantiate<BeerEngine::GameObject>("assets/Prefabs/item.prefab");
			mapBlocGO->transform.position = pos;
			// mapBlocGO->transform.scale = glm::vec3(0.5, 0.5, 0.5);
			return (mapBlocGO);
		}

		Game::Component::IA *Map::addIA(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 pos)
		{
			// do not use current scene due to loading system (the loaded scene only becomes current after init)
			auto iaGO = _gameObject->_scene.instantiate<BeerEngine::GameObject>();
				iaGO->name = "IA";
				iaGO->transform.position = pos;
				// iaGO->transform.scale = glm::vec3(1, 1, 1);
				iaGO->transform.scale = glm::vec3(0.03, 0.03, 0.03);
				auto collider = iaGO->AddComponent<BeerEngine::Component::CircleCollider>();
					collider->_radius = 0.4f;
					collider->colliderType = BeerEngine::Component::ONLY_OTHER;
				auto breakable = iaGO->AddComponent<Game::Component::Breakable>();
					GameManager::GetInstance().registerEnemy(breakable);
				auto modelRenderer = iaGO->AddComponent<BeerEngine::Component::ModelRenderer>();
					modelRenderer->load("assets/models/bombermanRunTest.fbx");
					// modelRenderer->load("assets/models/Rock/rock.obj");
					modelRenderer->setAnimationSpeed("idle", 0.25);
					modelRenderer->setLoopAnimation(true);
					// modelRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);

					int texID = rand() % 4;
					while (std::find(takenIATextures.begin(), takenIATextures.end(), texID) != takenIATextures.end())
					{
						texID = (texID + 1) % 4;
					}
					auto *iaTex = Assets::GetTexture(Game::Component::IA::textures[texID]);
					takenIATextures.push_back(texID);

					auto *iaMat = new BeerEngine::Graphics::AMaterial(shader);
						iaMat->setAlbedo(iaTex);
					modelRenderer->addMaterial(0, iaMat);
				auto character = iaGO->AddComponent<Game::Component::Character>();
					character->map = this;
				auto *ia = iaGO->AddComponent<Game::Component::IA>();
					ia->map = this;
				auto iaRB2D = iaGO->AddComponent<BeerEngine::Component::RigidBody2D>();
					iaRB2D->kinematic = BeerEngine::Component::RBType::Static;
			return (ia);
		}

		void	Map::setMap(std::vector<std::vector<int>>map, size_t sizeX, size_t sizeY)
		{
			_sizeX = sizeX;
			_sizeY = sizeY;
			_map = new int*[sizeY];
			for (std::size_t y = 0; y < sizeY; y++)
			{
				_map[y] = new int[sizeX];
				for (std::size_t x = 0; x < sizeX; x++)
					_map[y][x] = map[y][x];
			}
		}

		void	Map::setRandomMap(std::vector<std::vector<int>>map, size_t sizeX, size_t sizeY)
		{
			_sizeX = sizeX;
			_sizeY = sizeY;

				_map = new int*[sizeY];
				for (std::size_t y = 0; y < sizeY; y++)
				{
					_map[y] = new int[sizeX];
					for (std::size_t x = 0; x < sizeX; x++)
					{
						if (map[y][x] == 0)
						{
							int val = rand() % 100;
							if (val > 96)
								map[y][x] = I;
							else if (val > 25)
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
			// SEGFAULT ===> quand je rajoute || value == B
			// if (_map[y][x] == 2 && (value == 0 || value == B) && !(rand() % 3))
			// {
			// 	_map[y][x] = (value == B) ? B : I;
			// 	addItem(_shader, glm::vec3(-x + (_sizeX / 2), 0.5, -y + _sizeY));
			// }
			// else
			// 	_map[y][x] = value;

			// Les Item s'indique tout seul sur la map
			x = glm::clamp(x, 0, _sizeX - 1);
			y = glm::clamp(y, 0, _sizeY - 1);	
			if (_map[y][x] == 2 && (value == 0 || value == B) && !(rand() % 2))
				addItem(_shader, glm::vec3(-x + (_sizeX / 2), 0.5, -y + _sizeY));
			_map[y][x] = value;

        }

		void Map::mapUpdate(glm::vec3 pos, int value)
		{
			glm::vec2 Mpos = worldToMap(glm::vec3(pos.x, 0, pos.z));
			mapUpdate(static_cast<int>(Mpos.x), static_cast<int>(Mpos.y), value);
		}

		void	Map::drawMap()
		{
			int type = 0;
			bool playerSpawn = false;

			for (int row = 0; row < _sizeY; row++)
			{
				for (int col = 0; col < _sizeX; col++)
				{
					bool spawnIA;
					type = _map[row][col];
					switch (type)
					{
						case 1:
							addCrate<BeerEngine::Component::BoxCollider2D>(_shader, glm::vec3(1), glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY), BeerEngine::Component::RBType::Kinematic);
							break;
						case V:
							addCrate<BeerEngine::Component::BoxCollider2D>(_shader, glm::vec3(0.9), glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY), BeerEngine::Component::RBType::None);
							break;
						case 2:
						case E:
							addDestoyableCrate<BeerEngine::Component::BoxCollider2D>(_shader, glm::vec3(1), glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY), BeerEngine::Component::RBType::Kinematic);
							break;
						case P:
							if (!playerSpawn)
							{
								_player->_gameObject->transform.position = glm::vec3(-col + (_sizeX / 2), 0, -row + _sizeY);
								playerSpawn = true;
							}
							break;
						case Q:
							if (_IAs.size() < 3)
								_IAs.push_back(addIA(_shader, glm::vec3(-col + (_sizeX / 2), 0, -row + _sizeY)));
							break;
						case S:
							spawnIA = (rand() % 4 != 0 || playerSpawn ? true : false);
							if (spawnIA && _IAs.size() < 3)
								_IAs.push_back(addIA(_shader, glm::vec3(-col + (_sizeX / 2), 0, -row + _sizeY)));
							else
							{
								_player->_gameObject->transform.position = glm::vec3(-col + (_sizeX / 2), 0, -row + _sizeY);
								playerSpawn = true;
							}
							break;
						case I:
							addItem(_shader, glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY));
							break;
						case J:
							addItem(_shader, glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY), ItemType::ExplosionBoost);
							break;
						case U:
							addItem(_shader, glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY), ItemType::Antidote);
							break;
						case H:
							addItem(_shader, glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY), ItemType::AntidoteDeco);
							break;
						case F:
							addItem(_shader, glm::vec3(-col + (_sizeX / 2), 0.5, -row + _sizeY), ItemType::FireDeco);
							break;

					}
				}
			}
		}

		void    Map::renderUI(struct nk_context *ctx)
		{
			(void)ctx;
			// auto mapWidth = 270;
			// auto mapHeight = 430;
			// auto rect = nk_rect(0, BeerEngine::Window::GetInstance()->getHeight() - mapHeight, mapWidth, mapHeight);
			// if (nk_begin(ctx, "Map", rect, NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_CLOSABLE))
            // {
			// 	nk_layout_row_dynamic(ctx, 20, 1);
			// 	// if (_player)
			// 	// {
	        //     //     nk_label(ctx, "position", NK_TEXT_LEFT);
			// 	// 	nk_layout_row_dynamic(ctx, 20, 1);
	        //     //     nk_label(ctx, glm::to_string(worldToMap(_player->_gameObject->transform.position)).c_str(), NK_TEXT_LEFT);
			// 	// }
			// 	nk_layout_row_dynamic(ctx, 20, 1);
            //     nk_label(ctx, "map", NK_TEXT_LEFT);
			// 	for (int row = 0; row < _sizeY; row++)
			// 	{
			// 		std::stringstream ss;
			// 		for (int col = 0; col < _sizeX; col++)
			// 			ss << std::setw(2) << _map[row][col];
			// 		nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
			// 	}
            // }
            // nk_end(ctx);
			// if (uiInit)
			// {
			// 	nk_window_set_position(ctx, "Map", nk_vec2(0, BeerEngine::Window::GetInstance()->getHeight() - mapHeight));
			// 	nk_window_collapse(ctx, "Map", NK_MINIMIZED);
			// 	uiInit = false;
			// }
		}

		glm::vec2		Map::worldToMap(glm::vec3 pos)
		{
			return glm::vec2(round((pos.x - (_sizeX / 2)) * (-1)), round(_sizeY - pos.z));
		}

		glm::vec3		Map::mapToWorld(glm::vec2 pos, float y)
		{
			return glm::vec3(-pos.x + (_sizeX / 2), y, -pos.y + _sizeY);
		}

		bool			Map::hasBreakable(void)
		{
			for (int y = 0; y < _sizeY; y++)
			{
				for (int x = 0; x < _sizeX; x++)
					if (_map[y][x] == 2 || _map[y][x] == E)
						return (true);
			}
			return (false);
		}

		bool			Map::hasBlock(int id)
		{
			for (int y = 0; y < _sizeY; y++)
			{
				for (int x = 0; x < _sizeX; x++)
					if (_map[y][x] == id)
						return (true);
			}
			return (false);
		}

		bool			Map::hasCharacter(glm::vec2 pos)
		{
			if (_player && worldToMap(_player->_gameObject->transform.position) == pos)
				return (true);
			for (Game::Component::IA *ia : _IAs)
			{
				if (!ia->_gameObject)
				{
					std::cerr << "Potential segfault !" << std::endl;
					return (false);
				}
				if (worldToMap(ia->_gameObject->transform.position) == pos) // *******  Segfault ******* //
					return (true);
			}
			return (false);
		}

		int				Map::getCaseValue(glm::vec2 pos)
		{
			int x = glm::clamp(static_cast<int>(pos.x), 0, _sizeX - 1);
			int y = glm::clamp(static_cast<int>(pos.y), 0, _sizeY - 1);			
			return (_map[y][x]);
		}

		bool			Map::hasWall(glm::vec2 pos)
		{
			int x = glm::clamp(static_cast<int>(pos.x), 0, _sizeX - 1);
			int y = glm::clamp(static_cast<int>(pos.y), 0, _sizeY - 1);	
			if (_map[y][x] == 1)
				return (true);
			return (false);
		}

		bool			Map::hasBomb(glm::vec3 pos)
		{
			int x = static_cast<int>(worldToMap(pos).x);
			int y = static_cast<int>(worldToMap(pos).y);
			if (_map[y][x] == B)
				return (true);
			return (false);
		}

		bool			Map::canWalk(glm::vec2 pos)
		{
			int x = static_cast<int>(pos.x);
			int y = static_cast<int>(pos.y);
			if ((_map[y][x] == 0 || _map[y][x] == -1 || _map[y][x] == 8 || _map[y][x] == 9))// && !hasCharacter(glm::vec2(x, y)))
				return true;
			return false;
		}

		bool			Map::canWalk(glm::vec3 pos)
		{
			int x = static_cast<int>(worldToMap(pos).x);
			int y = static_cast<int>(worldToMap(pos).y);
			if (canWalk(glm::vec2(x, y)))
				return true;
			return false;
		}

		nlohmann::json	Map::serialize()
		{
			auto j = Component::serialize();

			nlohmann::json map;
			for(int y = 0; y < _sizeY; y++)
			{
				nlohmann::json mapLine;
				for(int x = 0; x < _sizeX; x++)
				{
					mapLine.push_back(_map[y][x]);
				}
				map.push_back(mapLine);
			}

			j.merge_patch({
				{"componentClass", type},
				{"sizeX", _sizeX},
				{"sizeY", _sizeY},
				{"map", map},
				{"player", SERIALIZE_BY_ID(this->_player)},
				{"shader", _shader},
			});
			return j;
		}

		void Map::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			Component::deserialize(j, loader);
			this->_sizeX = j.at("sizeX");
			this->_sizeY = j.at("sizeY");
			std::vector<std::vector<int>> map = j.at("map");
			// std::cout << j.at("map") << std::endl;
			// std::cout << "map : " << std::endl;
			// for (int y = 0; y < _sizeY; y++)
			// {
			// 	for (int x = 0; x < _sizeX; x++)
			// 	{
			// 		std::cout << " " << map[y][x];
			// 	}
			// 	std::cout << std::endl;
			// }
			this->setMap(map, this->_sizeX, this->_sizeY);

			DESERIALIZE_BY_ID(this->_player, Player, "player", loader);
			this->_shader = BeerEngine::Graphics::ShaderProgram::Deserialize(j.at("shader"), loader);
		}

		REGISTER_COMPONENT_CPP(Map)
    }
}
