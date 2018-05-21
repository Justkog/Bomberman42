#include "Game/LevelEnd.hpp"
#include <Core/Graphics/Lights/DirectionalLight.hpp>
#include "Core/Component/ModelRenderer.hpp"
#include "Core/Component/MeshRenderer.hpp"
#include "Core/Graphics/Graphics.hpp"
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
#include "Game/SceneBasics.hpp"

void    LevelEnd::init(void)
{
	// std::cout << "init level6 scene" << std::endl;

	BeerEngine::Graphics::Cubemap *skyboxCubemap = new BeerEngine::Graphics::Cubemap("assets/skyboxes/raregardener-cartoonskybox-04-blue.jpg", 512);
	setSkybox(skyboxCubemap);

	// Shader
	auto shader = Assets::GetShaderProgram("shaders/basic_v.glsl", "shaders/basic_f.glsl");
	// BeerEngine::Graphics::AMaterial *material = new BeerEngine::Graphics::AMaterial(shader);
	// material->setColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));

	// GameObject
	// BeerEngine::Component::ModelRenderer *modelRenderer;

	// Camera
	auto cameraGO = instantiate<BeerEngine::GameObject>();

	auto soundManager = cameraGO->AddComponent<Game::Component::AudioManager>();
	soundManager->setClip("assets/sounds/portal.ogg");
	soundManager->audioType = Game::Component::Music;

	Game::SceneBasics::CreateCameraBasics(cameraGO);

	auto gameManager = cameraGO->GetComponent<Game::Component::GameManager>();
	cameraGO->GetComponent<Game::Component::Settings>()->audioManager = soundManager;
	gameManager->audioManager = soundManager;

	gameManager->storyMode = true;

	cameraGO->GetComponent<Game::Component::VictoryMenu>()->sceneLoader.name = "SceneMain";
	cameraGO->GetComponent<Game::Component::GameOverMenu>()->sceneLoader.name = "SceneMain";
	cameraGO->GetComponent<Game::Component::InGameMenu>()->sceneLoader.name = "SceneMain";
	
	cameraGO->GetComponent<Game::Component::CameraController>()->setEndingCamera(13, 11);

	auto winText = instantiate<BeerEngine::GameObject>();
	auto winTextRender = winText->AddComponent<BeerEngine::Component::MeshRenderer>();
	winTextRender->setMesh(Assets::GetModel("assets/models/WIN.obj"));
	auto winMat = new BeerEngine::Graphics::AMaterial(BeerEngine::Graphics::Graphics::defaultShader, glm::vec4(1.0f));
	winTextRender->setMaterial(winMat);
	winMat->setAlbedo(BeerEngine::Graphics::Graphics::whiteTexture);
	winText->transform.position = glm::vec3(0, 7, 30);
	winText->transform.scale = glm::vec3(5, 5, 5);
	winText->transform.rotation = glm::angleAxis((float)3.14f, glm::vec3(0, 1, 0));

	// Player
	auto playerGO = instantiate<BeerEngine::GameObject>();
	Game::SceneBasics::CreatePlayerBasics(playerGO, gameManager, 0);
	auto player = playerGO->GetComponent<Game::Component::Player>();
	auto character = playerGO->GetComponent<Game::Component::Character>();

	// // Player
	// auto playerGO = instantiate<BeerEngine::GameObject>();
	// playerGO->name = "player";
	// modelRenderer = playerGO->AddComponent<BeerEngine::Component::ModelRenderer>();
	// modelRenderer->load("assets/models/bombermanRunTest.fbx");
	// auto *playerTex = Assets::GetTexture("assets/textures/body.png");
	// auto *playerMat = new BeerEngine::Graphics::AMaterial(shader);
	// playerMat->setAlbedo(playerTex);
	// modelRenderer->addMaterial(0, playerMat);
	// playerGO->transform.scale = glm::vec3(0.03, 0.03, 0.03);
	// auto *character = playerGO->AddComponent<Game::Component::Character>();
	// 	character->_maxBomb = 0;
	// 	character->_bombNb = character->_maxBomb;
	// auto *breakable = playerGO->AddComponent<Game::Component::Breakable>();
	// auto *player = playerGO->AddComponent<Game::Component::Player>();
	// auto playerColl = playerGO->AddComponent<BeerEngine::Component::CircleCollider>();
	// 	playerColl->colliderType = BeerEngine::Component::ONLY_OTHER;
	// 	playerColl->_radius = 0.4;
	// auto playerRB2D = playerGO->AddComponent<BeerEngine::Component::RigidBody2D>();
	// 	playerRB2D->kinematic = BeerEngine::Component::RBType::None;
	// playerGO->AddComponent<BeerEngine::Audio::AudioListener>();
	// auto as2 = playerGO->AddComponent<BeerEngine::Audio::AudioSource>();
	// auto itemAs = playerGO->AddComponent<BeerEngine::Audio::AudioSource>();
	// player->srcAudio = as2;
	// player->itemSrcAudio = itemAs;
	// gameManager->playerBreakable = breakable;
	// modelRenderer->setAnimation("idle");
	// modelRenderer->setAnimationSpeed("idle", 0.25);
	// modelRenderer->setLoopAnimation(true);
	// modelRenderer->playAnimation();

	//instantiate map
	auto MapGO = instantiate<BeerEngine::GameObject>();
	MapGO->name = "map";
	auto map = MapGO->AddComponent<Game::Component::Map>();
	map->_player = player;
	map->_shader = shader; // E eclater, U Objectif, J boost, V Movable, P player
	std::vector<int> line0 {1,1,1,1,1,1,1,1,1,1,1,1,1};
	std::vector<int> line1 {1,F,0,0,H,0,0,0,H,0,0,F,1};
	std::vector<int> line2 {1,0,H,0,0,0,0,0,0,0,H,0,1};
	std::vector<int> line3 {1,0,0,0,0,0,P,0,0,0,0,0,1};
	std::vector<int> line4 {1,H,0,0,0,0,0,0,0,0,0,H,1};
	std::vector<int> line5 {1,0,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line6 {1,0,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line7 {1,0,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line8 {1,0,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line9 {1,F,0,0,0,0,0,0,0,0,0,F,1};
	std::vector<int> line10{1,1,1,1,1,1,1,1,1,1,1,1,1};
	std::vector<std::vector<int>> tab{line0,line1,line2,line3,line4,line5,line6,line7,line8,line9,line10};
	map->setMap(tab, line0.size(), tab.size());

	character->map = map;

	BeerEngine::Graphics::DirectionalLight *light = instantiateLight<BeerEngine::Graphics::DirectionalLight>();
	light->setDirection(glm::normalize(glm::vec3(1, 2, -1)));
	light->setColor(glm::vec4(1, 0.9, 0.8, 1));
	light->setIntensity(1.5f);

	// Plane
	Game::SceneBasics::GeneratePlane(
		this,
		"assets/textures/grass.png", 
		glm::vec2(80, 80), 
		glm::vec2(0.5, 0.5), 
		glm::vec3(-3, 0, 6), 
		glm::vec3(40, 1, 40)
	);

	// Plane MAP
	Game::SceneBasics::GeneratePlane(
		this,
		"assets/textures/ground_color.png", 
		glm::vec2(12, 11), 
		glm::vec2(0.5, 0), 
		glm::vec3(0, 0.03, 5), 
		glm::vec3(6, 1, 5.5)
	);

	Game::SceneBasics::GenerateDecorations(this, glm::vec2(24, 15), glm::vec2(-24, 0), glm::vec2(7, 12), glm::vec2(-7, 0));

	std::cout << "saving scene.." << std::endl;
	this->save("assets/scenes/LevelEnd.scene");
}
