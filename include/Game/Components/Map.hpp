#ifndef BE_GAME_COMPONENT_MAP_HPP
#define BE_GAME_COMPONENT_MAP_HPP

#include "Core/Component/Component.hpp"
#include "Core/GameObject.hpp"
#include "Core/Transform.hpp"
#include "Core/BeerEngine.hpp"
#include "Game/Assets.hpp"
#include "Game/Components/Player.hpp"
#include "Game/Components/Character.hpp"
#include "Game/Components/Settings.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/Component/RigidBody2D.hpp"
#include "Game/Components/Item.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Component/IUI.hpp"

#define S -1 //spawn position
#define I 9 //Item

namespace Game
{
	namespace Component
	{
		class Map : public BeerEngine::Component::Component,
						public BeerEngine::Component::IUI
		{
		protected:
			BeerEngine::Transform	&_transform;

		public:
            Map(BeerEngine::GameObject *gameObject);

            virtual void    start(void);
			void			setMap(std::vector<std::vector<int>>map, size_t sizeX, size_t sizeY);
       		virtual void    mapUpdate(int x, int y);
			void			drawMap(BeerEngine::Graphics::ShaderProgram *shader);
			virtual void    renderUI(struct nk_context *ctx);
			glm::vec2		worldToMap(glm::vec3 pos);

			int								**_map;
			BeerEngine::GameObject			*_player;
			int	_sizeX;
			int	_sizeY;

			template <typename T>
			BeerEngine::GameObject *addCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, bool kinematic)
			{

				BeerEngine::Component::MeshRenderer *meshRenderer;
				auto mapBlocGO = _gameObject->_scene.instantiate<BeerEngine::GameObject>();
				mapBlocGO->name = "map block";
				meshRenderer = mapBlocGO->AddComponent<BeerEngine::Component::MeshRenderer>();
				meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
				auto *mapBlocTex = Assets::GetTexture("assets/textures/crate1_diffuse.png"); //BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_diffuse.png");
				auto *mapBlocMat = new BeerEngine::Graphics::AMaterial(shader);
				mapBlocMat->setAlbedo(mapBlocTex);
				meshRenderer->setMaterial(mapBlocMat);
				mapBlocGO->transform.position = pos;
				mapBlocGO->transform.scale = scale;
				auto blockColl = mapBlocGO->AddComponent<T>();
				if (!kinematic)
				{
					auto rb2d = mapBlocGO->AddComponent<BeerEngine::Component::RigidBody2D>();
					rb2d->kinematic = kinematic;
					rb2d->mass = 1.0f;
				}

				return (mapBlocGO);
			}

			BeerEngine::GameObject *addItem(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 pos)
			{

				auto itemGO = addCrate<BeerEngine::Component::CircleCollider>(shader, glm::vec3(0.5, 0.5, 0.5), pos, true);
				itemGO->name = "item";
				itemGO->AddComponent<Game::Component::Item>();
				auto itemColl = itemGO->GetComponent<BeerEngine::Component::CircleCollider>();
				itemColl->_isTrigger = true;
				return itemGO;
			}

			// BeerEngine::GameObject *addPlayer(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 pos)
			// {
			// 	BeerEngine::Component::MeshRenderer *meshRenderer;
			// 	auto playerGO = _gameObject->_scene.instantiate<BeerEngine::GameObject>();
			// 	playerGO->name = "player";
			// 	meshRenderer = playerGO->AddComponent<BeerEngine::Component::MeshRenderer>();
			// 	meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
			// 	auto *playerTex = BeerEngine::Graphics::Texture::LoadPNG("assets/textures/player2.png");
			// 	auto *playerMat = new BeerEngine::Graphics::AMaterial(shader);
			// 	playerMat->setAlbedo(playerTex);
			// 	meshRenderer->setMaterial(playerMat);
			// 	playerGO->transform.position = pos;
			// 	playerGO->transform.scale = glm::vec3(1, 1, 1);
			// 	auto *character = playerGO->AddComponent<Game::Component::Character>();
			// 	auto *player = playerGO->AddComponent<Game::Component::Player>();
			// 	auto *settings = playerGO->AddComponent<Game::Component::Settings>();
			// 	auto playerColl = playerGO->AddComponent<BeerEngine::Component::CircleCollider>();
			// 	auto rb2d = playerGO->AddComponent<BeerEngine::Component::RigidBody2D>();
			// 	rb2d->kinematic = false;
			// 	rb2d->mass = 1.0f;
            //
			// 	return (playerGO);
			// }
		};
	}
}

#endif
