#ifndef BE_GAME_COMPONENT_MAP_HPP
#define BE_GAME_COMPONENT_MAP_HPP

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/GameObject.hpp"
#include "Core/Transform.hpp"
#include "Core/BeerEngine.hpp"
#include "Game/Assets.hpp"
#include "Game/Components/Settings.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/Component/RigidBody2D.hpp"
#include "Game/Components/Item.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Component/IUI.hpp"
#include "Core/Component/IStart.hpp"
#include "Game/Components/Player.hpp"
#include "Core/Component/MeshRenderer.hpp"
#include "Game/Components/Breakable.hpp"

#define S -1 //spawn position
#define E 10 // Empty breakable
#define I 9 //Item
#define B 3 //Bomb
#define P -2 //spawn player
#define Q -3 //spawn ia
#define J 11 //Item Boost Explosion
#define U 20 //Objective (next level)
#define V 42 //Movable Crate

/*!
 * \file Map.hpp
 * \brief Component qui gère toute la zone de jeu
 * \author stmartin, qhonore, jblondea
 */
namespace Game
{
	namespace Component
	{
		/*! \class Map
		* \brief La classe Map gère les GameObjects du niveau, l'apparition des items, etc...
		*/
		class Map : public BeerEngine::Component::Component,
						public BeerEngine::Component::IStart,
						public BeerEngine::Component::IUI
		{
		protected:
			BeerEngine::Transform	&_transform;

		private:
			Map();
			Map(const Map &val);
			Map &operator=(const Map &val);

		public:
			static Map		*instance;
            Map(BeerEngine::GameObject *gameObject);
			~Map();

            virtual void    start(void);
			void			setMap(std::vector<std::vector<int>>map, size_t sizeX, size_t sizeY);
			void			setRandomMap(std::vector<std::vector<int>>map, size_t sizeX, size_t sizeY);
       		virtual void    mapUpdate(int x, int y, int value);
			void			drawMap();
			virtual void    renderUI(struct nk_context *ctx);
			glm::vec2		worldToMap(glm::vec3 pos);
			glm::vec3		mapToWorld(glm::vec2 pos, float y = 0);
			bool			hasBreakable(void);
			bool			hasBlock(int id);
			bool			hasCharacter(glm::vec2 pos);
			int				getCaseValue(glm::vec2 pos);
			bool			hasWall(glm::vec2 pos);
			bool			hasBomb(glm::vec3 pos);
			bool			canWalk(glm::vec2 pos);
			bool			canWalk(glm::vec3 pos);

			int								**_map;
			int	_sizeX;
			int	_sizeY;

			Game::Component::Player				*_player;
			std::vector<Game::Component::IA*>	_IAs;
			BeerEngine::Graphics::ShaderProgram	*_shader;

			BeerEngine::Graphics::Texture 	*itemSpeedBoostTex;
			BeerEngine::Graphics::Texture 	*itemBombTex;
			BeerEngine::Graphics::Texture 	*itemRangeTex;
			BeerEngine::Graphics::Mesh		*itemSpeedBoostMesh;
			BeerEngine::Graphics::Mesh		*itemBombMesh;
			BeerEngine::Graphics::Mesh		*itemRangeMesh;

			bool uiInit;
			std::vector<int> 				takenIATextures;

			void mapUpdate(glm::vec3 pos, int value);

			BeerEngine::GameObject *createCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, BeerEngine::Component::RBType kinematic);
			BeerEngine::GameObject *addItem(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 pos, int type = -1);
			BeerEngine::GameObject *createItem(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 pos);
			Game::Component::IA *addIA(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 pos);

			template <typename T>
			BeerEngine::GameObject *addCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, BeerEngine::Component::RBType kinematic)
			{
				BeerEngine::Component::MeshRenderer *meshRenderer;
				auto mapBlocGO = _gameObject->_scene.instantiate<BeerEngine::GameObject>();
				mapBlocGO->name = "map block";
				meshRenderer = mapBlocGO->AddComponent<BeerEngine::Component::MeshRenderer>();
				meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
				auto *mapBlocTex = Assets::GetTexture("assets/textures/wall.png");
				auto *mapBlocNrm = Assets::GetTexture("assets/textures/wall_normal.png");
				auto *mapBlocBmp = Assets::GetTexture("assets/textures/wall_bump.png");
				auto *mapBlocMat = new BeerEngine::Graphics::AMaterial(shader);
				mapBlocMat->setAlbedo(mapBlocTex);
				mapBlocMat->setNormal(mapBlocNrm);
				// mapBlocMat->setBump(mapBlocBmp);
				meshRenderer->setMaterial(mapBlocMat);
				mapBlocGO->transform.position = pos;
				mapBlocGO->transform.scale = scale;
				mapBlocGO->AddComponent<T>();
				if (kinematic != BeerEngine::Component::RBType::Kinematic)
				{
					auto rb2d = mapBlocGO->AddComponent<BeerEngine::Component::RigidBody2D>();
					rb2d->kinematic = kinematic;
					rb2d->mass = 1.0f;
				}
				return (mapBlocGO);
			}

			template <typename T>
			BeerEngine::GameObject *addDestoyableCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, BeerEngine::Component::RBType kinematic)
			{
				BeerEngine::Component::MeshRenderer *meshRenderer;
				auto mapBlocGO = _gameObject->_scene.instantiate<BeerEngine::GameObject>();
				mapBlocGO->name = "destroyable block";
				meshRenderer = mapBlocGO->AddComponent<BeerEngine::Component::MeshRenderer>();
				meshRenderer->setMesh("assets/models/Rock/rock.obj");
				auto *mapBlocTex = Assets::GetTexture("assets/models/Rock/rock_color.png");
				auto *mapBlocMat = new BeerEngine::Graphics::AMaterial(shader);
				mapBlocMat->setAlbedo(mapBlocTex);
				meshRenderer->setMaterial(mapBlocMat);
				mapBlocGO->transform.position = pos;
				mapBlocGO->transform.scale = scale;
				mapBlocGO->AddComponent<T>();
				auto destroyable = mapBlocGO->AddComponent<Game::Component::Breakable>();
				destroyable->onDestruction.bind(&Map::mapUpdate, this);
				if (kinematic != BeerEngine::Component::RBType::Kinematic)
				{
					auto rb2d = mapBlocGO->AddComponent<BeerEngine::Component::RigidBody2D>();
					rb2d->kinematic = kinematic;
					rb2d->mass = 1.0f;
				}

				return (mapBlocGO);
			}

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif
