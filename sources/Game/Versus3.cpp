#include "Game/Versus3.hpp"
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

void    Versus3::init(void)
{
	std::cout << "init Versus3 scene" << std::endl;

	BeerEngine::Graphics::Cubemap *skyboxCubemap = new BeerEngine::Graphics::Cubemap("assets/skyboxes/pano_1.jpg", 512);
	setSkybox(skyboxCubemap);

	// Shader
	auto shader = Assets::GetShaderProgram("shaders/basic_v.glsl", "shaders/basic_f.glsl");
	BeerEngine::Graphics::AMaterial *material = new BeerEngine::Graphics::AMaterial(shader);
	material->setColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));

	// GameObject
	BeerEngine::Component::ModelRenderer *modelRenderer;

	// Camera
	auto cameraGO = instantiate<BeerEngine::GameObject>();

	auto soundManager = cameraGO->AddComponent<Game::Component::AudioManager>();
	soundManager->setClip("assets/sounds/clint.ogg");
	soundManager->audioType = Game::Component::Music;

	Game::SceneBasics::CreateCameraBasics(cameraGO);

	auto gameManager = cameraGO->GetComponent<Game::Component::GameManager>();
	cameraGO->GetComponent<Game::Component::Settings>()->audioManager = soundManager;
	gameManager->audioManager = soundManager;

	gameManager->storyMode = false;

	cameraGO->GetComponent<Game::Component::VictoryMenu>()->sceneLoader.name = "Random";
	cameraGO->GetComponent<Game::Component::GameOverMenu>()->sceneLoader.name = "Versus3";
	cameraGO->GetComponent<Game::Component::InGameMenu>()->sceneLoader.name = "Versus3";

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
	map->_shader = shader;
	std::vector<int>  line0{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	std::vector<int>  line1{1,S,0,2,0,2,0,2,0,2,0,2,0,2,0,S,1};
	std::vector<int>  line2{1,0,1,1,1,1,1,1,2,1,1,1,1,1,1,0,1};
	std::vector<int>  line3{1,2,1,0,2,0,2,0,2,0,2,0,2,0,1,2,1};
	std::vector<int>  line4{1,2,1,2,1,1,1,1,1,1,1,1,1,2,1,2,1};
	std::vector<int>  line5{1,0,1,0,1,2,0,2,2,2,0,2,1,0,1,0,1};
	std::vector<int>  line6{1,2,0,2,0,0,2,1,I,1,2,0,0,2,0,2,1};
	std::vector<int>  line7{1,0,1,0,1,2,0,2,2,2,0,2,1,0,1,0,1};
	std::vector<int>  line8{1,2,1,2,1,1,1,1,1,1,1,1,1,2,1,2,1};
	std::vector<int>  line9{1,2,1,0,2,0,2,0,2,0,2,0,2,0,1,2,1};
	std::vector<int> line10{1,0,1,1,1,1,1,1,2,1,1,1,1,1,1,0,1};
	std::vector<int> line11{1,S,0,2,0,2,0,2,0,2,0,2,0,2,0,S,1};
	std::vector<int> line12{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	std::vector<std::vector<int>> tab{line0,line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,line11,line12};
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
	mapMeshRenderer->setMesh(BeerEngine::Graphics::Graphics::LoadPlane(glm::vec2(17, 13), glm::vec2(0, 0)));
	mapMeshRenderer->setMaterial(material);
	planeTex = BeerEngine::Graphics::Texture::LoadJPG("assets/textures/ground_color.png");
	planeMat = new BeerEngine::Graphics::AMaterial(shader);
	planeMat->setAlbedo(planeTex);
	mapMeshRenderer->setMaterial(planeMat);
	mapGO->transform.position = glm::vec3(0, 0.03, 7);
	mapGO->transform.scale = glm::vec3(8.5, 1, 6.5);

	Game::SceneBasics::GenerateDecorations(this, glm::vec2(20, 15), glm::vec2(-20, 0), glm::vec2(10, 14), glm::vec2(-10, 0));

	std::cout << "saving scene.." << std::endl;
	this->save("assets/scenes/Versus3.scene");
}
