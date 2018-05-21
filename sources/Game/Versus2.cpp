#include "Game/Versus2.hpp"
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
#include "Game/Components/TimeUI.hpp"
#include "Game/Components/StartTimerUI.hpp"
#include "Game/Components/ItemsUI.hpp"
#include "Game/Components/AudioManager.hpp"
#include "Game/Components/CameraController.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Game/Assets.hpp"
#include "Core/Graphics/Cubemap.hpp"
#include "Game/SceneBasics.hpp"

void    Versus2::init(void)
{
	// std::cout << "init Versus2 scene" << std::endl;

	BeerEngine::Graphics::Cubemap *skyboxCubemap = new BeerEngine::Graphics::Cubemap("assets/skyboxes/pano_1.jpg", 512);
	setSkybox(skyboxCubemap);

	// Shader
	auto shader = Assets::GetShaderProgram("shaders/basic_v.glsl", "shaders/basic_f.glsl");

	// GameObject
	// BeerEngine::Component::ModelRenderer *modelRenderer;

	// Camera
	auto cameraGO = instantiate<BeerEngine::GameObject>();

	auto soundManager = cameraGO->AddComponent<Game::Component::AudioManager>();
	soundManager->setClip("assets/sounds/wiggle.ogg");
	soundManager->audioType = Game::Component::Music;

	Game::SceneBasics::CreateCameraBasics(cameraGO);

	auto gameManager = cameraGO->GetComponent<Game::Component::GameManager>();
	cameraGO->GetComponent<Game::Component::Settings>()->audioManager = soundManager;
	gameManager->audioManager = soundManager;

	gameManager->storyMode = false;

	cameraGO->GetComponent<Game::Component::VictoryMenu>()->sceneLoader.name = "Versus3";
	cameraGO->GetComponent<Game::Component::GameOverMenu>()->sceneLoader.name = "Versus2";
	cameraGO->GetComponent<Game::Component::InGameMenu>()->sceneLoader.name = "Versus2";

	// cameraGO->GetComponent<Game::Component::LevelInstructions>()->setInstructions({
	// 	{"test instr 1", 2.0}
	// });

	// Player
	auto playerGO = instantiate<BeerEngine::GameObject>();
	Game::SceneBasics::CreatePlayerBasics(playerGO, gameManager, 1);
	auto player = playerGO->GetComponent<Game::Component::Player>();
	auto character = playerGO->GetComponent<Game::Component::Character>();

	//instantiate map
	auto MapGO = instantiate<BeerEngine::GameObject>();
	MapGO->name = "map";
	auto map = MapGO->AddComponent<Game::Component::Map>();
	map->_player = player;
	map->_shader = shader;  // S : Spawn, I : Item, 2 : Break, 1 : Wall
	std::vector<int>  line0{0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0};
	std::vector<int>  line1{0,0,0,0,1,2,2,2,2,2,2,2,1,0,0,0,0};
	std::vector<int>  line2{0,0,0,0,1,2,2,0,1,0,2,2,1,0,0,0,0};
	std::vector<int>  line3{0,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0};
	std::vector<int>  line4{1,1,1,1,1,2,1,S,1,S,1,2,1,1,1,1,1};
	std::vector<int>  line5{1,0,2,2,2,0,0,1,1,1,0,0,2,2,2,0,1};
	std::vector<int>  line6{1,2,1,I,1,1,2,2,I,2,2,1,1,I,1,2,1};
	std::vector<int>  line7{1,0,2,2,2,0,0,1,1,1,0,0,2,2,2,0,1};
	std::vector<int>  line8{1,1,1,1,1,2,1,S,1,S,1,2,1,1,1,1,1};
	std::vector<int>  line9{0,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0};
	std::vector<int> line10{0,0,0,0,1,2,2,0,1,0,2,2,1,0,0,0,0};
	std::vector<int> line11{0,0,0,0,1,2,2,2,2,2,2,2,1,0,0,0,0};
	std::vector<int> line12{0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0};
	std::vector<std::vector<int>> tab{line0,line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,line11,line12};
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
		glm::vec2(9, 13), 
		glm::vec2(0, 0), 
		glm::vec3(0, 0.03, 7), 
		glm::vec3(4.5, 1, 6.5)
	);

	Game::SceneBasics::GeneratePlane(
		this,
		"assets/textures/ground_color.png", 
		glm::vec2(4, 4), 
		glm::vec2(0, 0), 
		glm::vec3(6.5, 0.03, 6.5), 
		glm::vec3(2, 1, 2)
	);

	Game::SceneBasics::GeneratePlane(
		this,
		"assets/textures/ground_color.png", 
		glm::vec2(4, 4), 
		glm::vec2(0, 0), 
		glm::vec3(-6.5, 0.03, 6.5), 
		glm::vec3(2, 1, 2)
	);

	Game::SceneBasics::GenerateDecorations(this, glm::vec2(20, 15), glm::vec2(-20, 0), glm::vec2(10, 14), glm::vec2(-10, 0));

	std::cout << "saving scene.." << std::endl;
	this->save("assets/scenes/Versus2.scene");
}
