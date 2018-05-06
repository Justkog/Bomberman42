#include "Game/SceneTest.hpp"
#include "Game/Components/Settings.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/Component/RigidBody2D.hpp"
#include "Core/Component/RaysRenderer.hpp"
#include "Core/Component/ParticleBase.hpp"
#include "Core/Component/ParticleExplode.hpp"
#include "Game/Components/Player.hpp"
#include "Game/Components/Character.hpp"
#include "Game/Components/Item.hpp"
#include "Game/Components/Map.hpp"

#include "Game/Components/CameraController.hpp"
#include "Game/Components/MouseRayTest.hpp"
#include "Game/Components/BeerRoutineTester.hpp"
#include "Game/CameraTest.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Json/Json.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/ShaderProgram.hpp"
#include "Game/Assets.hpp"

template<typename T>
BeerEngine::GameObject *SceneTest::addCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, bool kinematic)
{
	BeerEngine::Component::MeshRenderer *meshRenderer;
	auto mapBlocGO = instantiate<BeerEngine::GameObject>();
	mapBlocGO->name = "map block";
	meshRenderer = mapBlocGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
	auto *mapBlocTex = Assets::GetTexture("assets/textures/crate1_diffuse.png"); //BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_diffuse.png");
	auto *mapBlocMat = new BeerEngine::Graphics::AMaterial(shader);
	mapBlocMat->setAlbedo(mapBlocTex);
	meshRenderer->setMaterial(mapBlocMat);
	mapBlocGO->transform.position = pos;
	mapBlocGO->transform.scale = scale;
	auto blockColl = mapBlocGO->AddComponent<T>();
	if (!kinematic)
	{
		auto rb2d = mapBlocGO->AddComponent<BeerEngine::Component::RigidBody2D>();
		rb2d->kinematic = kinematic;
		rb2d->mass = 1.0f;
	}

	return (mapBlocGO);
}

void    SceneTest::init(void)
{
	// this->load("test2.scene");
	// this->save("destest.scene");


	// return;

	std::cout << "init test scene" << "\n";

	// Shader
	BeerEngine::Graphics::ShaderProgram *shader = new BeerEngine::Graphics::ShaderProgram(2);
	shader->load(0, GL_VERTEX_SHADER,
		BeerEngine::IO::FileUtils::LoadFile("shaders/basic_v.glsl").c_str()
	);
	shader->load(1, GL_FRAGMENT_SHADER,
		BeerEngine::IO::FileUtils::LoadFile("shaders/basic_f.glsl").c_str()
	);
	shader->compile();
	BeerEngine::Graphics::AMaterial *material = new BeerEngine::Graphics::AMaterial(shader);
	material->setColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));

	// prefab test
	// auto crateGO = addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(10, 0, 5), true);
	// crateGO->save("Prefabs/crate.prefab");

	// auto crate2 = instantiate<BeerEngine::GameObject>("Prefabs/crate.prefab");
	// crate2->transform.position.x += 2;
	// crate2->save("Prefabs/reserializedCrate.prefab");

	// return;
	// cube 1
	// Texture
	BeerEngine::Graphics::Texture *crate = Assets::GetTexture("assets/textures/crate1_diffuse.png"); //BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_diffuse.png");
	BeerEngine::Graphics::Texture *crate_normal = BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_normal.png");
	BeerEngine::Graphics::Texture *crate_bump = BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_bump.png");

	// Material
	BeerEngine::Graphics::AMaterial *materialA = new BeerEngine::Graphics::AMaterial(shader);
	materialA->setAlbedo(crate);
	materialA->setNormal(crate_normal);
	materialA->setBump(crate_bump);
	BeerEngine::Graphics::AMaterial *materialB = new BeerEngine::Graphics::AMaterial(shader);
	materialB->setAlbedo(crate);
	materialB->setNormal(crate_normal);
	BeerEngine::Graphics::AMaterial *materialC = new BeerEngine::Graphics::AMaterial(shader);
	materialC->setAlbedo(crate);
	BeerEngine::Graphics::AMaterial *material2 = new BeerEngine::Graphics::AMaterial(shader);
	material2->setColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
	// material2->setAlbedo(crate);

	// GameObject
	//
	BeerEngine::GameObject *gameObject;
	BeerEngine::Component::MeshRenderer *meshRenderer;

	auto linesGO = instantiate<BeerEngine::GameObject>();
	auto linesRenderer = linesGO->AddComponent<BeerEngine::Component::RaysRenderer>();
	linesGO->name = "lines Holder";

	// Camera
	BeerEngine::GameObject *cameraGO;
	cameraGO = instantiate<BeerEngine::GameObject>();
	cameraGO->name = "Camera";

	Game::Component::CameraController *cameraController = cameraGO->AddComponent<Game::Component::CameraController>();
	auto mouseRay = cameraGO->AddComponent<Game::Component::MouseRayTest>();
	mouseRay->linesRenderer = linesRenderer;
	

	// BeerEngine::Camera::main->transform.position = glm::vec3(-1, 1, 0);
	// BeerEngine::Camera::main->transform.rotation = glm::quat(glm::vec3(glm::radians(0.0f), glm::radians(45.0f), 0.0f));
	/*glm::vec3 v = BeerEngine::Camera::main->transform.forward();
	BeerEngine::Camera::main->transform.translate(-v);*/


	// Player
	auto playerGO = instantiate<BeerEngine::GameObject>();
	playerGO->name = "player";
	meshRenderer = playerGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
	auto *playerTex = BeerEngine::Graphics::Texture::LoadPNG("assets/textures/player2.png");
	auto *playerMat = new BeerEngine::Graphics::AMaterial(shader);
	playerMat->setAlbedo(playerTex);
	meshRenderer->setMaterial(playerMat);
	// playerGO->transform.position = glm::vec3(1, 0.5, 7);
	playerGO->transform.scale = glm::vec3(1, 1, 1);
	auto *character = playerGO->AddComponent<Game::Component::Character>();
	auto *player = playerGO->AddComponent<Game::Component::Player>();
	auto *routineTester = playerGO->AddComponent<Game::Component::BeerRoutineTester>();
	auto *settings = playerGO->AddComponent<Game::Component::Settings>();
	auto playerColl = playerGO->AddComponent<BeerEngine::Component::CircleCollider>();
	auto playerRB2D = playerGO->AddComponent<BeerEngine::Component::RigidBody2D>();
	playerRB2D->kinematic = false;

	// FPS Camera
	// instantiate<CameraTest>();


	auto MapGO = instantiate<BeerEngine::GameObject>();
		MapGO->name = "map";
	auto	map = MapGO->AddComponent<Game::Component::Map>();
	map->_player = player;
	std::vector<int> line0{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	std::vector<int> line1{1,S,0,0,0,0,0,0,0,0,0,0,0,0,0,S,1};
	std::vector<int> line2{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
	std::vector<int> line3{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line4{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
	std::vector<int> line5{1,0,0,0,0,0,0,I,0,0,0,0,0,0,0,0,1};
	std::vector<int> line6{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
	std::vector<int> line7{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line8{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
	std::vector<int> line9{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	std::vector<int> line10{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
	std::vector<int> line11{1,S,0,0,0,0,0,0,0,0,0,0,0,0,0,S,1};
	std::vector<int> line12{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	std::vector<std::vector<int>> tab{line0,line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,line11,line12};

	auto mapCrateGO = map->addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), true);
	mapCrateGO->save("Prefabs/mapCrate.prefab");
	auto itemGO = map->addItem(shader, glm::vec3(0, 0, 0));
	itemGO->save("Prefabs/item.prefab");
	
	map->setMap(tab, line0.size(), tab.size());
	map->drawMap(shader);

	// map->addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), true);
	auto mapCrateGO2 = instantiate<BeerEngine::GameObject>("Prefabs/mapCrate.prefab");
	std::cout << "mapCrateGO2 name : " << mapCrateGO2->name << "\n";	
	mapCrateGO2->save("Prefabs/reMapCrate.prefab");

	//test obj house
	auto objet = instantiate<BeerEngine::GameObject>();
	objet->name = "house";
	meshRenderer = objet->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh("assets/models/HouseOBJ/house_01.obj");
	auto *objetTex = BeerEngine::Graphics::Texture::LoadJPG("assets/models/HouseOBJ/DSC_5871_.jpg");
	auto *objetMat = new BeerEngine::Graphics::AMaterial(shader);
	objetMat->setAlbedo(objetTex);
	meshRenderer->setMaterial(objetMat);
	objet->transform.position = glm::vec3(-5, 0, 16.5);
	objet->transform.scale = glm::vec3(0.05, 0.05, 0.05);
	objet->transform.rotation = glm::vec3(0, 0, 0);

	auto house2 = instantiate<BeerEngine::GameObject>();
	house2->name = "house2";
	meshRenderer = house2->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh("assets/models/HouseOBJ/house_01.obj");
	auto *house2Tex = BeerEngine::Graphics::Texture::LoadJPG("assets/models/HouseOBJ/DSC_5871_.jpg");
	auto *house2Mat = new BeerEngine::Graphics::AMaterial(shader);
	house2Mat->setAlbedo(house2Tex);
	meshRenderer->setMaterial(house2Mat);
	house2->transform.position = glm::vec3(4.5, 0, 14.4);
	house2->transform.scale = glm::vec3(0.05, 0.05, 0.05);
	house2->transform.rotation = glm::vec3(0, 3.14, 0);
	// Player
	// auto playerGO = instantiate<BeerEngine::GameObject>();
	// playerGO->name = "player";
	// meshRenderer = playerGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	// meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
	// auto *playerTex = BeerEngine::Graphics::Texture::LoadPNG("assets/textures/player2.png");
	// auto *playerMat = new BeerEngine::Graphics::AMaterial(shader);
	// playerMat->setAlbedo(playerTex);
	// meshRenderer->setMaterial(playerMat);
	// playerGO->transform.position = glm::vec3(1, 0.5, 7);
	// playerGO->transform.scale = glm::vec3(1, 1, 1);
	// auto *character = playerGO->AddComponent<Game::Component::Character>();
	// auto *player = playerGO->AddComponent<Game::Component::Player>();
	// auto *settings = playerGO->AddComponent<Game::Component::Settings>();
	// auto playerColl = playerGO->AddComponent<BeerEngine::Component::CircleCollider>();
	// auto playerRB2D = playerGO->AddComponent<BeerEngine::Component::RigidBody2D>();
	// playerRB2D->kinematic = false;

 // test obj old

	auto Old = instantiate<BeerEngine::GameObject>();
	Old->name = "old";
	meshRenderer = Old->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh("assets/models/Old_man/muro.obj");
	auto *OldTex = BeerEngine::Graphics::Texture::LoadTGA("assets/models/Old_man/Muro_head_dm.tga");
	auto *OldMat = new BeerEngine::Graphics::AMaterial(shader);
	OldMat->setAlbedo(OldTex);
	meshRenderer->setMaterial(OldMat);
	Old->transform.position = glm::vec3(1, 0.5, 10);
	Old->transform.scale = glm::vec3(0.012, 0.012, 0.012);
	Old->transform.rotation = glm::vec3(0, -3.14, 0);

	// plane
	BeerEngine::GameObject *mapGO;
	mapGO = instantiate<BeerEngine::GameObject>();
	BeerEngine::Component::MeshRenderer *mapMeshRenderer = mapGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	mapMeshRenderer->setMesh(BeerEngine::Graphics::Graphics::plane);
	mapMeshRenderer->setMaterial(material);
	mapGO->transform.position = glm::vec3(-3, 0, 6);
	mapGO->transform.scale = glm::vec3(40, 1, 40);


	this->save("test2.scene");
	std::cout << "init end" << "\n";
}
