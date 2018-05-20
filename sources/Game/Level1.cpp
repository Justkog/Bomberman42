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
	BeerEngine::Graphics::AMaterial *material = new BeerEngine::Graphics::AMaterial(shader);
	material->setColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));

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
		{"test instr 1", 2.0}
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
	mapMeshRenderer->setMesh(BeerEngine::Graphics::Graphics::LoadPlane(glm::vec2(7, 9), glm::vec2(0)));
	mapMeshRenderer->setMaterial(material);
	planeTex = BeerEngine::Graphics::Texture::LoadJPG("assets/textures/ground_color.png");
	planeMat = new BeerEngine::Graphics::AMaterial(shader);
	planeMat->setAlbedo(planeTex);
	mapMeshRenderer->setMaterial(planeMat);
	mapGO->transform.position = glm::vec3(0, 0.03, 5);
	mapGO->transform.scale = glm::vec3(3.5, 1, 4.5);


	Game::SceneBasics::GenerateDecorations(this, glm::vec2(15, 15), glm::vec2(-15, 0), glm::vec2(5, 10), glm::vec2(-5, 0), 100);

	// auto objet = instantiate<BeerEngine::GameObject>();
	// Game::SceneBasics::CreateModelBasics(
	// 	objet,
	// 	"assets/models/Decoration/pineTree/Models/pine_tree_free.fbx",
	// 	"assets/models/Decoration/pineTree/Textures/pine_tree_red_SC.tga",
	// 	BeerEngine::Transform(
	// 		glm::vec3(5, 0, 5),
	// 		glm::vec3(0, 0, 0),
	// 		glm::vec3(0.005, 0.005, 0.005)
	// 	)
	// );

	// objet = instantiate<BeerEngine::GameObject>();
	// Game::SceneBasics::CreateModelBasics(
	// 	objet,
	// 	"assets/models/Decoration/Tree/Models/grassland_tree_free.fbx",
	// 	"assets/models/Decoration/Tree/Textures/trees_autumn_SC.tga",
	// 	BeerEngine::Transform(
	// 		glm::vec3(-5, 0, 5),
	// 		glm::vec3(0, 0, 0),
	// 		glm::vec3(0.005, 0.005, 0.005)
	// 	)
	// );

	// objet = instantiate<BeerEngine::GameObject>();
	// Game::SceneBasics::CreateModelBasics(
	// 	objet,
	// 	"assets/models/Decoration/trees/Models/rock.fbx",
	// 	"assets/models/Decoration/trees/Textures/rock.png",
	// 	BeerEngine::Transform(
	// 		glm::vec3(5, 0, 7),
	// 		glm::vec3(0, 0, 0),
	// 		glm::vec3(1.5, 1.5, 1.5)
	// 	)
	// );

	// objet->name = "tree1";
	// auto modelRenderer = objet->AddComponent<BeerEngine::Component::ModelRenderer>();
	// modelRenderer->load("assets/models/Decoration/pineTree/Models/pine_tree_free.fbx");
	// auto objetTex = BeerEngine::Graphics::Texture::LoadTGA("assets/models/Decoration/pineTree/Textures/pine_tree_red_SC.tga");
	// auto objetMat = new BeerEngine::Graphics::AMaterial(shader);
	// objetMat->setAlbedo(objetTex);
	// modelRenderer->addMaterial(0, objetMat);
	// objet->transform.position = glm::vec3(6, 0, 3);
	// objet->transform.scale = glm::vec3(0.005, 0.005, 0.005);
	// objet->transform.rotation = glm::vec3(0, 0, 0);

	// objet = instantiate<BeerEngine::GameObject>();
	// objet->name = "tree2";
	// modelRenderer = objet->AddComponent<BeerEngine::Component::ModelRenderer>();
	// modelRenderer->load("assets/models/Decoration/Tree/Models/grassland_tree_free.fbx");
	// objetTex = BeerEngine::Graphics::Texture::LoadTGA("assets/models/Decoration/Tree/Textures/trees_autumn_SC.tga");
	// objetMat = new BeerEngine::Graphics::AMaterial(shader);
	// objetMat->setAlbedo(objetTex);
	// modelRenderer->addMaterial(0, objetMat);
	// objet->transform.position = glm::vec3(-6, 0, 3);
	// objet->transform.scale = glm::vec3(0.005, 0.005, 0.005);
	// objet->transform.rotation = glm::vec3(0, 0, 0);

	// objet = instantiate<BeerEngine::GameObject>();
	// objet->name = "tree3";
	// modelRenderer = objet->AddComponent<BeerEngine::Component::ModelRenderer>();
	// modelRenderer->load("assets/models/Decoration/Tree/Models/grassland_tree_free.fbx");
	// objetTex = BeerEngine::Graphics::Texture::LoadTGA("assets/models/Decoration/Tree/Textures/trees_autumn_SC.tga");
	// objetMat = new BeerEngine::Graphics::AMaterial(shader);
	// objetMat->setAlbedo(objetTex);
	// modelRenderer->addMaterial(0, objetMat);
	// objet->transform.position = glm::vec3(6, 0, 7.5);
	// objet->transform.scale = glm::vec3(0.005, 0.005, 0.005);
	// objet->transform.rotation = glm::vec3(0, 0, 0);

	// objet = instantiate<BeerEngine::GameObject>();
	// objet->name = "tree4";
	// modelRenderer = objet->AddComponent<BeerEngine::Component::ModelRenderer>();
	// modelRenderer->load("assets/models/Decoration/pineTree/Models/pine_tree_free.fbx");
	// objetTex = BeerEngine::Graphics::Texture::LoadTGA("assets/models/Decoration/pineTree/Textures/pine_tree_red_SC.tga");
	// objetMat = new BeerEngine::Graphics::AMaterial(shader);
	// objetMat->setAlbedo(objetTex);
	// modelRenderer->addMaterial(0, objetMat);
	// objet->transform.position = glm::vec3(-6, 0, 7.5);
	// objet->transform.scale = glm::vec3(0.005, 0.005, 0.005);
	// objet->transform.rotation = glm::vec3(0, 0, 0);

	// objet = instantiate<BeerEngine::GameObject>();
	// objet->name = "tree5";
	// modelRenderer = objet->AddComponent<BeerEngine::Component::ModelRenderer>();
	// modelRenderer->load("assets/models/Decoration/pineTree/Models/pine_tree_free.fbx");
	// objetTex = BeerEngine::Graphics::Texture::LoadTGA("assets/models/Decoration/pineTree/Textures/pine_tree_red_SC.tga");
	// objetMat = new BeerEngine::Graphics::AMaterial(shader);
	// objetMat->setAlbedo(objetTex);
	// modelRenderer->addMaterial(0, objetMat);
	// objet->transform.position = glm::vec3(3, 0, 12);
	// objet->transform.scale = glm::vec3(0.005, 0.005, 0.005);
	// objet->transform.rotation = glm::vec3(0, 0, 0);

	// objet = instantiate<BeerEngine::GameObject>();
	// objet->name = "tree6";
	// modelRenderer = objet->AddComponent<BeerEngine::Component::ModelRenderer>();
	// modelRenderer->load("assets/models/Decoration/pineTree/Models/pine_tree_free.fbx");
	// objetTex = BeerEngine::Graphics::Texture::LoadTGA("assets/models/Decoration/pineTree/Textures/pine_tree_red_SC.tga");
	// objetMat = new BeerEngine::Graphics::AMaterial(shader);
	// objetMat->setAlbedo(objetTex);
	// modelRenderer->addMaterial(0, objetMat);
	// objet->transform.position = glm::vec3(-3, 0, 12);
	// objet->transform.scale = glm::vec3(0.005, 0.005, 0.005);
	// objet->transform.rotation = glm::vec3(0, 0, 0);

	// objet = instantiate<BeerEngine::GameObject>();
	// objet->name = "tree7";
	// modelRenderer = objet->AddComponent<BeerEngine::Component::ModelRenderer>();
	// modelRenderer->load("assets/models/Decoration/trees/Models/rock.fbx");
	// objetTex = BeerEngine::Graphics::Texture::LoadPNG("assets/models/Decoration/trees/Textures/rock.png");
	// objetMat = new BeerEngine::Graphics::AMaterial(shader);
	// objetMat->setAlbedo(objetTex);
	// modelRenderer->addMaterial(0, objetMat);
	// objet->transform.position = glm::vec3(-6, 0, 6);
	// objet->transform.scale = glm::vec3(1.5, 1.5, 1.5);
	// objet->transform.rotation = glm::vec3(0, 0, 0);

	// objet = instantiate<BeerEngine::GameObject>();
	// objet->name = "tree8";
	// modelRenderer = objet->AddComponent<BeerEngine::Component::ModelRenderer>();
	// modelRenderer->load("assets/models/Decoration/trees/Models/fence.fbx");
	// objetTex = BeerEngine::Graphics::Texture::LoadPNG("assets/models/Decoration/trees/Textures/fence.png");
	// objetMat = new BeerEngine::Graphics::AMaterial(shader);
	// objetMat->setAlbedo(objetTex);
	// modelRenderer->addMaterial(0, objetMat);
	// objet->transform.position = glm::vec3(6, 0, 6);
	// objet->transform.scale = glm::vec3(0.5, 0.5, 0.5);
	// objet->transform.rotation = glm::vec3(0, 0, 0);

	// objet = instantiate<BeerEngine::GameObject>();
	// objet->name = "tree9";
	// modelRenderer = objet->AddComponent<BeerEngine::Component::ModelRenderer>();
	// modelRenderer->load("assets/models/Decoration/trees/Models/fence.fbx");
	// objetTex = BeerEngine::Graphics::Texture::LoadPNG("assets/models/Decoration/trees/Textures/fence.png");
	// objetMat = new BeerEngine::Graphics::AMaterial(shader);
	// objetMat->setAlbedo(objetTex);
	// modelRenderer->addMaterial(0, objetMat);
	// objet->transform.position = glm::vec3(6, 0, 5);
	// objet->transform.scale = glm::vec3(0.5, 0.5, 0.5);
	// objet->transform.rotation = glm::vec3(0, 2, 0);

	std::cout << "saving scene.." << std::endl;
	this->save("assets/scenes/Level1.scene");
}

Level1 Level1::instance = Level1();
