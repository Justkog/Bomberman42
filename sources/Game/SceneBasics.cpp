#include "Game/SceneBasics.hpp"
#include <Core/Graphics/Lights/DirectionalLight.hpp>
#include "Core/Component/ModelRenderer.hpp"
#include "Core/GameObject.hpp"
#include "Game/Components/Player.hpp"
#include "Game/Components/Character.hpp"
#include "Game/Components/Map.hpp"
#include "Game/Components/GameManager.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Game/Components/InGameMenu.hpp"
#include "Game/Components/GameOverMenu.hpp"
#include "Game/Components/VictoryMenu.hpp"
#include "Game/Components/GameProgression.hpp"
#include "Game/Components/TimeUI.hpp"
#include "Game/Components/Message.hpp"
#include "Game/Components/StartTimerUI.hpp"
#include "Game/Components/LevelInstructions.hpp"
#include "Game/Components/ItemsUI.hpp"
#include "Game/Components/Message.hpp"
#include "Game/Components/AudioManager.hpp"
#include "Game/Components/CameraController.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Game/Assets.hpp"
#include "Core/Graphics/Cubemap.hpp"
#include "Game/SceneBasics.hpp"


namespace Game
{
	void	SceneBasics::CreateCameraBasics(BeerEngine::GameObject *cameraGO)
	{
		cameraGO->name = "Camera";
		cameraGO->AddComponent<Game::Component::CameraController>();

		// Managers
		auto gameManager = cameraGO->AddComponent<Game::Component::GameManager>();

		// Misc
		auto settings = cameraGO->AddComponent<Game::Component::Settings>();
		auto gameProgression = cameraGO->AddComponent<Game::Component::GameProgression>();

		// UI
		auto uiManager = cameraGO->AddComponent<Game::Component::UIThemeManager>();
		auto inGameMenu = cameraGO->AddComponent<Game::Component::InGameMenu>();
		auto gameOverMenu = cameraGO->AddComponent<Game::Component::GameOverMenu>();
		auto victoryMenu = cameraGO->AddComponent<Game::Component::VictoryMenu>();
		auto timeUI = cameraGO->AddComponent<Game::Component::TimeUI>();
		auto startTimerUI = cameraGO->AddComponent<Game::Component::StartTimerUI>();
		auto itemsUI = cameraGO->AddComponent<Game::Component::ItemsUI>();
		auto message = cameraGO->AddComponent<Game::Component::Message>();
		auto levelInstructions = cameraGO->AddComponent<Game::Component::LevelInstructions>();

		gameManager->inGameMenu = inGameMenu;
		gameManager->gameOverMenu = gameOverMenu;
		gameManager->victoryMenu = victoryMenu;
		gameManager->timeUI = timeUI;
		gameManager->startTimerUI = startTimerUI;
		gameManager->gameProgression = gameProgression;
		gameManager->levelInstructions = levelInstructions;

		inGameMenu->uiManager = uiManager;
		gameOverMenu->uiManager = uiManager;
		victoryMenu->uiManager = uiManager;
		startTimerUI->uiManager = uiManager;
		message->uiManager = uiManager;
		timeUI->uiManager = uiManager;
		itemsUI->uiManager = uiManager;

		levelInstructions->message = message;

		inGameMenu->setActive(false);
		gameOverMenu->setActive(false);
		victoryMenu->setActive(false);
		message->setActive(false);
	}

	void	SceneBasics::CreatePlayerBasics(BeerEngine::GameObject *playerGO, Game::Component::GameManager *gameManager, int bombNumber)
	{
		auto shader = Assets::GetShaderProgram("shaders/basic_v.glsl", "shaders/basic_f.glsl");
		playerGO->name = "player";
		auto modelRenderer = playerGO->AddComponent<BeerEngine::Component::ModelRenderer>();
		modelRenderer->load("assets/models/bombermanRunTest.fbx");
		auto *playerTex = Assets::GetTexture("assets/textures/body.png");
		auto *playerMat = new BeerEngine::Graphics::AMaterial(shader);
		playerMat->setAlbedo(playerTex);
		modelRenderer->addMaterial(0, playerMat);
		playerGO->transform.scale = glm::vec3(0.03, 0.03, 0.03);
		auto *character = playerGO->AddComponent<Game::Component::Character>();
			character->_maxBomb = bombNumber;
			character->_bombNb = character->_maxBomb;
		auto *breakable = playerGO->AddComponent<Game::Component::Breakable>();
		auto *player = playerGO->AddComponent<Game::Component::Player>();
		auto playerColl = playerGO->AddComponent<BeerEngine::Component::CircleCollider>();
			playerColl->colliderType = BeerEngine::Component::ONLY_OTHER;
			playerColl->_radius = 0.4;
		auto playerRB2D = playerGO->AddComponent<BeerEngine::Component::RigidBody2D>();
			playerRB2D->kinematic = BeerEngine::Component::RBType::None;
		playerGO->AddComponent<BeerEngine::Audio::AudioListener>();
		auto as2 = playerGO->AddComponent<BeerEngine::Audio::AudioSource>();
		auto itemAs = playerGO->AddComponent<BeerEngine::Audio::AudioSource>();
		player->srcAudio = as2;
		player->itemSrcAudio = itemAs;
		gameManager->playerBreakable = breakable;
		modelRenderer->setAnimation("idle");
		modelRenderer->setAnimationSpeed("idle", 0.25);
		modelRenderer->setLoopAnimation(true);
		modelRenderer->playAnimation();
	}

	void	SceneBasics::CreateModelBasics(BeerEngine::GameObject *objet, const std::string &model, const std::string &texture, const BeerEngine::Transform &transform)
	{
		static int modelID = 0;

		auto shader = Assets::GetShaderProgram("shaders/basic_v.glsl", "shaders/basic_f.glsl");
		objet->name = "model_" + std::to_string(modelID);
		auto modelRenderer = objet->AddComponent<BeerEngine::Component::ModelRenderer>();
		modelRenderer->load(model);
		auto objetTex = Assets::GetTexture(texture);
		auto objetMat = new BeerEngine::Graphics::AMaterial(shader);
		objetMat->setAlbedo(objetTex);
		modelRenderer->addMaterial(0, objetMat);
		objet->transform.position = transform.position;
		objet->transform.scale = transform.scale;
		objet->transform.rotation = transform.rotation;
		modelID++;
	}

	void SceneBasics::GenerateDecorations(BeerEngine::AScene *scene, glm::vec2 max, glm::vec2 min, glm::vec2 mapA, glm::vec2 mapB)
    {
		static std::vector<std::string> models = {
			"assets/models/Decoration/trees/Models/rock.fbx",
			"assets/models/Decoration/pineTree/Models/pine_tree_free.fbx",
			"assets/models/Decoration/Tree/Models/grassland_tree_free.fbx",
			"assets/models/Decoration/trees/Models/tree1.fbx",
			"assets/models/Decoration/trees/Models/tree2.fbx"
		};
		static std::vector<std::string> textures = {
			"assets/models/Decoration/trees/Textures/rock.png",
			"assets/models/Decoration/pineTree/Textures/pine_tree_red_SC.tga",
			"assets/models/Decoration/Tree/Textures/trees_autumn_SC.tga",
			"assets/models/Decoration/trees/Textures/colors.png",
			"assets/models/Decoration/trees/Textures/colors.png"
		};

		for (int x = 0; x < max.x - min.x + 1; x++)
		{
			for (int y = 0; y < max.y - min.x + 1; y++)
			{
				if (x % 2 == 0)
					continue;
				if (y % 2 == 0)
					continue;
				if (rand() % 20 > 12)
					continue;
				int xx = x + min.x;
				int yy = y + min.y;

				if (xx < mapA.x && xx > mapB.x && yy < mapA.y && yy > mapB.y)
					continue;

				int index = rand() % models.size();

				auto objet = scene->instantiate<BeerEngine::GameObject>();
				Game::SceneBasics::CreateModelBasics(
					objet,
					models[index],
					textures[index],
					BeerEngine::Transform(
						glm::vec3(xx, 0, yy),
						glm::vec3(0, glm::radians((float) (rand() % 360)), 0),
						glm::vec3(1.5, 1.5, 1.5)
					)
				);
			}	
		}
    }

	void SceneBasics::GeneratePlane(BeerEngine::AScene *scene, 
		std::string texturePath, 
		glm::vec2 tiling, glm::vec2 offset, 
		glm::vec3 position, glm::vec3 scale)
	{
		auto mapGO = scene->instantiate<BeerEngine::GameObject>();
		BeerEngine::Component::MeshRenderer *mapMeshRenderer = mapGO->AddComponent<BeerEngine::Component::MeshRenderer>();
		mapMeshRenderer->setMesh(BeerEngine::Graphics::Graphics::LoadPlane(tiling, offset));
		auto planeTex = Assets::GetTexture(texturePath);
		auto planeMat = new BeerEngine::Graphics::AMaterial(Assets::GetShaderProgram("shaders/basic_v.glsl", "shaders/basic_f.glsl"));
		planeMat->setAlbedo(planeTex);
		mapMeshRenderer->setMaterial(planeMat);
		mapGO->transform.position = position;
		mapGO->transform.scale = scale;
	}

	void SceneBasics::GenerateModel(BeerEngine::AScene *scene,
		std::string name,
		std::string meshPath,
		std::string albedoPath,
		glm::vec3 position,
		glm::vec3 rotation,
		glm::vec3 scale)
	{
		auto objet = scene->instantiate<BeerEngine::GameObject>();
		objet->name = name;
		auto meshRenderer = objet->AddComponent<BeerEngine::Component::MeshRenderer>();
		meshRenderer->setMesh(meshPath);
		auto objetTex = Assets::GetTexture(albedoPath);
		auto objetMat = new BeerEngine::Graphics::AMaterial(Assets::GetShaderProgram("shaders/basic_v.glsl", "shaders/basic_f.glsl"));
		objetMat->setAlbedo(objetTex);
		meshRenderer->setMaterial(objetMat);
		objet->transform.position = position;
		objet->transform.scale = scale;
		objet->transform.rotation = rotation;
	}
}