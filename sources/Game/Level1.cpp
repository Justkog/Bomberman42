#include "Game/Level1.hpp"
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


void    Level1::init(void)
{
	std::cout << "init level1 scene" << std::endl;

	BeerEngine::Graphics::Cubemap *skyboxCubemap = new BeerEngine::Graphics::Cubemap("assets/skyboxes/pano_1.jpg", 512);
	setSkybox(skyboxCubemap);

	// Shader
	auto shader = Assets::GetShaderProgram("shaders/basic_v.glsl", "shaders/basic_f.glsl");

	// Camera
	auto cameraGO = instantiate<BeerEngine::GameObject>();

	auto soundManager = cameraGO->AddComponent<Game::Component::AudioManager>();
	soundManager->setClip("assets/sounds/clint.ogg");
	soundManager->audioType = Game::Component::Music;

	Game::SceneBasics::CreateCameraBasics(cameraGO);

	auto gameManager = cameraGO->GetComponent<Game::Component::GameManager>();
	cameraGO->GetComponent<Game::Component::Settings>()->audioManager = soundManager;
	gameManager->audioManager = soundManager;

	gameManager->storyMode = true;

	cameraGO->GetComponent<Game::Component::VictoryMenu>()->sceneLoader.name = "Level2";
	cameraGO->GetComponent<Game::Component::GameOverMenu>()->sceneLoader.name = "Level1";
	cameraGO->GetComponent<Game::Component::InGameMenu>()->sceneLoader.name = "Level1";

	cameraGO->GetComponent<Game::Component::LevelInstructions>()->setInstructions({
		{"Exploser tous les blocs.", 3.0},
		{"Recupere la bombe d'or!", 3.0}
	});

	// Player
	auto playerGO = instantiate<BeerEngine::GameObject>();
	Game::SceneBasics::CreatePlayerBasics(playerGO, gameManager, 3);
	auto player = playerGO->GetComponent<Game::Component::Player>();
	auto character = playerGO->GetComponent<Game::Component::Character>();

	//instantiate map
	auto MapGO = instantiate<BeerEngine::GameObject>();
	MapGO->name = "map";
	auto map = MapGO->AddComponent<Game::Component::Map>();
	map->_player = player;
	map->_shader = shader;
	std::vector<int> line0{1,1,1,1,1,1,1};
	std::vector<int> line1{1,0,1,U,1,0,1};
	std::vector<int> line2{1,0,1,E,1,0,1};
	std::vector<int> line3{1,0,1,E,1,0,1};
	std::vector<int> line4{1,0,E,J,E,0,1};
	std::vector<int> line5{1,0,1,E,1,0,1};
	std::vector<int> line6{1,0,0,E,0,0,1};
	std::vector<int> line7{1,0,0,P,0,0,1};
	std::vector<int> line8{1,1,1,1,1,1,1};
	std::vector<std::vector<int>> tab{line0,line1,line2,line3,line4,line5,line6,line7,line8};
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
		glm::vec2(7, 9), 
		glm::vec2(0), 
		glm::vec3(0, 0.03, 5), 
		glm::vec3(3.5, 1, 4.5)
	);

	Game::SceneBasics::GenerateDecorations(this, glm::vec2(12, 15), glm::vec2(-12, 0), glm::vec2(5, 10), glm::vec2(-5, 0));

	std::cout << "saving scene.." << std::endl;
	this->save("assets/scenes/Level1.scene");
}

Level1 Level1::instance = Level1();
