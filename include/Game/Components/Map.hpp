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
#define I 9 //Item
#define B 3 //Item

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
       		virtual void    mapUpdate(int x, int y, int value);
			void			drawMap(BeerEngine::Graphics::ShaderProgram *shader);
			virtual void    renderUI(struct nk_context *ctx);
			glm::vec2		worldToMap(glm::vec3 pos);
			glm::vec3		mapToWorld(glm::vec2 pos, float y = 0.5);
			bool			hasCharacter(glm::vec2 pos);
			bool			hasBomb(glm::vec3 pos);
			bool			canWalk(glm::vec2 pos);
			bool			canWalk(glm::vec3 pos);

			int								**_map;
			int	_sizeX;
			int	_sizeY;
			Game::Component::Player				*_player;
			BeerEngine::Graphics::ShaderProgram	*_shader;

			void mapUpdate(glm::vec3 pos, int value);

			BeerEngine::GameObject *createCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, BeerEngine::Component::RBType kinematic);
			BeerEngine::GameObject *addItem(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 pos);
			BeerEngine::GameObject *createItem(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 pos);

			template <typename T>
			BeerEngine::GameObject *addCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, BeerEngine::Component::RBType kinematic)
			{
				BeerEngine::Component::MeshRenderer *meshRenderer;
				auto mapBlocGO = _gameObject->_scene.instantiate<BeerEngine::GameObject>();
				mapBlocGO->name = "map block";
				meshRenderer = mapBlocGO->AddComponent<BeerEngine::Component::MeshRenderer>();
				meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
				auto *mapBlocTex = Assets::GetTexture("assets/textures/crate0_diffuse.png"); //BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_diffuse.png");
				auto *mapBlocMat = new BeerEngine::Graphics::AMaterial(shader);
				mapBlocMat->setAlbedo(mapBlocTex);
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
				meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
				auto *mapBlocTex = Assets::GetTexture("assets/textures/crate1_diffuse.png"); //BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_diffuse.png");
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

			virtual nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif
