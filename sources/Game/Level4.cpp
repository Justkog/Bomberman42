#include "Game/Level4.hpp"
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
#include "Game/Components/StartTimerUI.hpp"
#include "Game/Components/ItemsUI.hpp"
#include "Game/Components/AudioManager.hpp"
#include "Game/Components/CameraController.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Game/Assets.hpp"
#include "Core/Graphics/Cubemap.hpp"

void    Level4::init(void)
{
	std::cout << "init level4 scene" << std::endl;

	BeerEngine::Graphics::Cubemap *skyboxCubemap = new BeerEngine::Graphics::Cubemap("assets/skyboxes/pano_1.jpg", 512);
	setSkybox(skyboxCubemap);

	// Shader
	auto shader = Assets::GetShaderProgram("shaders/basic_v.glsl", "shaders/basic_f.glsl");
	BeerEngine::Graphics::AMaterial *material = new BeerEngine::Graphics::AMaterial(shader);
	material->setColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));

	// GameObject
	BeerEngine::Component::MeshRenderer *meshRenderer;
	BeerEngine::Component::ModelRenderer *modelRenderer;

	// Camera
	auto cameraGO = instantiate<BeerEngine::GameObject>();
	cameraGO->name = "Camera";

	// Managers
	auto gameManager = cameraGO->AddComponent<Game::Component::GameManager>();
	auto soundManager = cameraGO->AddComponent<Game::Component::AudioManager>();

	// Misc
	auto settings = cameraGO->AddComponent<Game::Component::Settings>();
	auto gameProgression = cameraGO->AddComponent<Game::Component::GameProgression>();
	auto cameraController = cameraGO->AddComponent<Game::Component::CameraController>();

	// UI
	auto uiManager = cameraGO->AddComponent<Game::Component::UIThemeManager>();
	auto inGameMenu = cameraGO->AddComponent<Game::Component::InGameMenu>();
	auto gameOverMenu = cameraGO->AddComponent<Game::Component::GameOverMenu>();
	auto victoryMenu = cameraGO->AddComponent<Game::Component::VictoryMenu>();
	auto timeUI = cameraGO->AddComponent<Game::Component::TimeUI>();
	auto startTimerUI = cameraGO->AddComponent<Game::Component::StartTimerUI>();
	auto itemsUI = cameraGO->AddComponent<Game::Component::ItemsUI>();

	soundManager->setClip("assets/sounds/clint.ogg");
	soundManager->audioType = Game::Component::Music;

	gameManager->inGameMenu = inGameMenu;
	gameManager->gameOverMenu = gameOverMenu;
	gameManager->victoryMenu = victoryMenu;
	gameManager->timeUI = timeUI;
	gameManager->startTimerUI = startTimerUI;
	gameManager->audioManager = soundManager;
	gameManager->gameProgression = gameProgression;
	gameManager->storyMode = true;

	inGameMenu->uiManager = uiManager;
	gameOverMenu->uiManager = uiManager;
	victoryMenu->uiManager = uiManager;
	startTimerUI->uiManager = uiManager;

	settings->audioManager = soundManager;

	inGameMenu->setActive(false);
	gameOverMenu->setActive(false);
	victoryMenu->setActive(false);

	timeUI->uiManager = uiManager;
	itemsUI->uiManager = uiManager;

	victoryMenu->sceneLoader.name = "Level5";
	gameOverMenu->sceneLoader.name = "Level4";
	inGameMenu->sceneLoader.name = "Level4";

	// Player
	auto playerGO = instantiate<BeerEngine::GameObject>();
	playerGO->name = "player";
	modelRenderer = playerGO->AddComponent<BeerEngine::Component::ModelRenderer>();
	modelRenderer->load("assets/models/bombermanRunTest.fbx");
	auto *playerTex = BeerEngine::Graphics::Texture::LoadPNG("assets/textures/body.png");
	auto *playerMat = new BeerEngine::Graphics::AMaterial(shader);
	playerMat->setAlbedo(playerTex);
	modelRenderer->addMaterial(0, playerMat);
	playerGO->transform.scale = glm::vec3(0.03, 0.03, 0.03);
	auto *character = playerGO->AddComponent<Game::Component::Character>();
		character->_maxBomb = 7;
		character->_bombNb = character->_maxBomb;
	auto *breakable = playerGO->AddComponent<Game::Component::Breakable>();
	auto *player = playerGO->AddComponent<Game::Component::Player>();
	auto playerColl = playerGO->AddComponent<BeerEngine::Component::CircleCollider>();
		playerColl->colliderType = BeerEngine::Component::ONLY_OTHER;
		playerColl->_radius = 0.4;
	auto playerRB2D = playerGO->AddComponent<BeerEngine::Component::RigidBody2D>();
		playerRB2D->kinematic = BeerEngine::Component::RBType::None;
	auto listener = playerGO->AddComponent<BeerEngine::Audio::AudioListener>();
	auto as2 = playerGO->AddComponent<BeerEngine::Audio::AudioSource>();
	auto itemAs = playerGO->AddComponent<BeerEngine::Audio::AudioSource>();
	player->srcAudio = as2;
	player->itemSrcAudio = itemAs;
	gameManager->playerBreakable = breakable;
	modelRenderer->setAnimation("idle");
	modelRenderer->setAnimationSpeed("idle", 0.25);
	modelRenderer->setLoopAnimation(true);
	modelRenderer->playAnimation();

	//instantiate map
	auto MapGO = instantiate<BeerEngine::GameObject>();
	MapGO->name = "map";
	auto map = MapGO->AddComponent<Game::Component::Map>();
	map->_player = player;
	map->_shader = shader;
	std::vector<int> line0 {1,1,1,1,1,1,1,1,1,1,1,1};
	std::vector<int> line1 {1,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line2 {1,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line3 {1,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line4 {1,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line5 {1,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line6 {1,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line7 {1,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line8 {1,0,0,0,1,V,1,0,0,0,0,1};
	std::vector<int> line9 {1,0,0,0,1,P,1,0,0,0,0,1};
	std::vector<int> line10{1,1,1,1,1,1,1,1,1,1,1,1};
	std::vector<std::vector<int>> tab{line0,line1,line2,line3,line4,line5,line6,line7,line8,line9,line10};
	map->setMap(tab, line0.size(), tab.size());

	character->map = map;

	BeerEngine::Graphics::DirectionalLight *light = instantiateLight<BeerEngine::Graphics::DirectionalLight>();
	light->setDirection(glm::normalize(glm::vec3(1, 2, -1)));
	light->setColor(glm::vec4(1, 0.9, 0.8, 1));
	light->setIntensity(1.5f);

	// Plane
	BeerEngine::GameObject *mapGO;
	mapGO = instantiate<BeerEngine::GameObject>();
	BeerEngine::Component::MeshRenderer *mapMeshRenderer = mapGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	mapMeshRenderer->setMesh(BeerEngine::Graphics::Graphics::LoadPlane(glm::vec2(80, 80), glm::vec2(0.5, 0.5)));
	mapMeshRenderer->setMaterial(material);
	auto planeTex = BeerEngine::Graphics::Texture::LoadJPG("assets/textures/grass.png");
	auto planeMat = new BeerEngine::Graphics::AMaterial(shader);
	planeMat->setAlbedo(planeTex);
	mapMeshRenderer->setMaterial(planeMat);
	mapGO->transform.position = glm::vec3(-3, 0, 6);
	mapGO->transform.scale = glm::vec3(40, 1, 40);

	// Plane MAP
	mapGO = instantiate<BeerEngine::GameObject>();
	mapMeshRenderer = mapGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	mapMeshRenderer->setMesh(BeerEngine::Graphics::Graphics::LoadPlane(glm::vec2(12, 11), glm::vec2(0.5, 0)));
	mapMeshRenderer->setMaterial(material);
	planeTex = BeerEngine::Graphics::Texture::LoadJPG("assets/textures/ground_color.png");
	planeMat = new BeerEngine::Graphics::AMaterial(shader);
	planeMat->setAlbedo(planeTex);
	mapMeshRenderer->setMaterial(planeMat);
	mapGO->transform.position = glm::vec3(0, 0.03, 5);
	mapGO->transform.scale = glm::vec3(6, 1, 5.5);

	std::cout << "saving scene.." << std::endl;
	this->save("assets/scenes/Level4.scene");
}
