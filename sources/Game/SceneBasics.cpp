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
		auto *playerTex = BeerEngine::Graphics::Texture::LoadPNG("assets/textures/body.png");
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
}