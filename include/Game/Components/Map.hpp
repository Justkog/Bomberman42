#ifndef BE_GAME_COMPONENT_MAP_HPP
#define BE_GAME_COMPONENT_MAP_HPP

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/GameObject.hpp"
#include "Core/Transform.hpp"
#include "Core/BeerEngine.hpp"
#include "Game/Assets.hpp"
#include "Game/Components/Character.hpp"
#include "Game/Components/Settings.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/Component/RigidBody2D.hpp"
#include "Game/Components/Item.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Component/IUI.hpp"
#include "Core/Component/IStart.hpp"
#include "Game/Components/Player.hpp"
#include "Game/Components/Breakable.hpp"

#define S -1 //spawn position
#define I 9 //Item

namespace Game
{
	namespace Component
	{
		class Map : public BeerEngine::Component::Component,
						public BeerEngine::Component::IStart,
						public BeerEngine::Component::IUI
		{
		protected:
			BeerEngine::Transform	&_transform;

		public:
            Map(BeerEngine::GameObject *gameObject);
			~Map();

            virtual void    start(void);
			void			setMap(std::vector<std::vector<int>>map, size_t sizeX, size_t sizeY);
       		virtual void    mapUpdate(int x, int y);
			void			drawMap(BeerEngine::Graphics::ShaderProgram *shader);
			virtual void    renderUI(struct nk_context *ctx);
			glm::vec2		worldToMap(glm::vec3 pos);
			glm::vec3		mapToWorld(glm::vec2 pos, float y = 0.5);

			int								**_map;
			int	_sizeX;
			int	_sizeY;
			Game::Component::Player			*_player;

			void setDestruction(float posX, float posY);

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
				mapBlocGO->AddComponent<T>();
				if (!kinematic)
				{
					auto rb2d = mapBlocGO->AddComponent<BeerEngine::Component::RigidBody2D>();
					rb2d->kinematic = kinematic;
					rb2d->mass = 1.0f;
				}

				return (mapBlocGO);
			}

			template <typename T>
			BeerEngine::GameObject *addDestoyableCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, bool kinematic)
			{

				BeerEngine::Component::MeshRenderer *meshRenderer;
				auto mapBlocGO = _gameObject->_scene.instantiate<BeerEngine::GameObject>();
				mapBlocGO->name = "destroyable block";
				meshRenderer = mapBlocGO->AddComponent<BeerEngine::Component::MeshRenderer>();
				meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
				auto *mapBlocTex = Assets::GetTexture("assets/textures/crate1_diffuse.png"); //BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_diffuse.png");
				auto *mapBlocMat = new BeerEngine::Graphics::AMaterial(shader);
				mapBlocMat->setAlbedo(mapBlocTex);
				meshRenderer->setMaterial(mapBlocMat);
				mapBlocGO->transform.position = pos;
				mapBlocGO->transform.scale = scale;
				mapBlocGO->AddComponent<T>();
				auto destroyable = mapBlocGO->AddComponent<Game::Component::Breakable>();
				destroyable->onDestruction.bind(&Map::setDestruction, this);
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
		};
	}
}

#endif
