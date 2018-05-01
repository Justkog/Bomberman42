#include "Game/SceneTest.hpp"
#include "Core/Graphics/Particles.hpp"
#include "Game/Components/Settings.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/Component/RigidBody2D.hpp"
#include "Game/Components/Player.hpp"
#include "Game/Components/Character.hpp"
#include "Game/Components/Item.hpp"
#include "Game/Components/CameraController.hpp"
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

	// Camera
	BeerEngine::GameObject *cameraGO;
	cameraGO = instantiate<BeerEngine::GameObject>();
	cameraGO->name = "Camera";

	Game::Component::CameraController *cameraController = cameraGO->AddComponent<Game::Component::CameraController>();

	// BeerEngine::Camera::main->transform.position = glm::vec3(-1, 1, 0);
	// BeerEngine::Camera::main->transform.rotation = glm::quat(glm::vec3(glm::radians(0.0f), glm::radians(45.0f), 0.0f));
	/*glm::vec3 v = BeerEngine::Camera::main->transform.forward();
	BeerEngine::Camera::main->transform.translate(-v);*/

	// FPS Camera
	// instantiate<CameraTest>();

	// Player

	auto playerGO = instantiate<BeerEngine::GameObject>();
	playerGO->name = "player";
	meshRenderer = playerGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
	auto *playerTex = BeerEngine::Graphics::Texture::LoadPNG("assets/textures/player2.png");
	auto *playerMat = new BeerEngine::Graphics::AMaterial(shader);
	playerMat->setAlbedo(playerTex);
	meshRenderer->setMaterial(playerMat);
	playerGO->transform.position = glm::vec3(1, 0.5, 7);
	playerGO->transform.scale = glm::vec3(1, 1, 1);
	auto *character = playerGO->AddComponent<Game::Component::Character>();
	auto *player = playerGO->AddComponent<Game::Component::Player>();
	auto *settings = playerGO->AddComponent<Game::Component::Settings>();
	auto playerColl = playerGO->AddComponent<BeerEngine::Component::CircleCollider>();
	auto playerRB2D = playerGO->AddComponent<BeerEngine::Component::RigidBody2D>();
	playerRB2D->kinematic = false;
	// playerColl->_kinematic = false;
//
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

 // test obj skull

	auto Skull = instantiate<BeerEngine::GameObject>();
	Skull->name = "skull";
	meshRenderer = Skull->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh("assets/models/Skull.obj");
	auto *SkullTex = BeerEngine::Graphics::Texture::LoadJPG("assets/models/HouseOBJ/DSC_5871_.jpg");
	auto *SkullMat = new BeerEngine::Graphics::AMaterial(shader);
	SkullMat->setAlbedo(SkullTex);
	meshRenderer->setMaterial(SkullMat);
	Skull->transform.position = glm::vec3(8, 0.5, 10);
	Skull->transform.scale = glm::vec3(0.005, 0.005, 0.005);
	Skull->transform.rotation = glm::vec3(-0.45, -3.14, 0);

//test obj house

	auto objet = instantiate<BeerEngine::GameObject>();
	objet->name = "house";
	meshRenderer = objet->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh("assets/models/HouseOBJ/house_01.obj");
	auto *objetTex = BeerEngine::Graphics::Texture::LoadJPG("assets/models/HouseOBJ/DSC_5871_.jpg");
	auto *objetMat = new BeerEngine::Graphics::AMaterial(shader);
	objetMat->setAlbedo(objetTex);
	meshRenderer->setMaterial(objetMat);
	objet->transform.position = glm::vec3(7, 0.5, 10);
	objet->transform.scale = glm::vec3(0.05, 0.05, 0.05);
	objet->transform.rotation = glm::vec3(0, -1.5, 0);


// //test obj car
//
// 	auto car = instantiate<BeerEngine::GameObject>();
// 	car->name = "car";
// 	meshRenderer = car->AddComponent<BeerEngine::Component::MeshRenderer>();
// 	meshRenderer->setMesh("assets/models/DodgeOBJ/Dodge_Chellenger_SRT10_OBJ.obj");
// 	auto *carTex = BeerEngine::Graphics::Texture::LoadJPG("assets/models/OrangeOBJ/Color.jpg");
// 	auto *carMat = new BeerEngine::Graphics::AMaterial(shader);
// 	carMat->setAlbedo(carTex);
// 	meshRenderer->setMaterial(carMat);
// 	car->transform.position = glm::vec3(0, 0.5, 10);
// 	car->transform.scale = glm::vec3(0.02, 0.02, 0.02);
// 	car->transform.rotation = glm::vec3(0, -1.5, 0);

//test obj bigmax

	auto bigmax = instantiate<BeerEngine::GameObject>();
	bigmax->name = "bigmax";
	meshRenderer = bigmax->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh("assets/models/BigMaxOBJ/Bigmax_White_OBJ.obj");
	auto *bigmaxTex = BeerEngine::Graphics::Texture::LoadJPG("assets/models/BigMaxOBJ/EyesWhite.jpg");
	auto *bigmaxMat = new BeerEngine::Graphics::AMaterial(shader);
	bigmaxMat->setAlbedo(bigmaxTex);
	meshRenderer->setMaterial(bigmaxMat);
	bigmax->transform.position = glm::vec3(-7, 0, 10);
	bigmax->transform.scale = glm::vec3(0.07, 0.07, 0.07);
	bigmax->transform.rotation = glm::vec3(0, 0.0f, 0);

	//test obj fourmi

		auto fourmi = instantiate<BeerEngine::GameObject>();
		fourmi->name = "fourmi";
		meshRenderer = fourmi->AddComponent<BeerEngine::Component::MeshRenderer>();
		meshRenderer->setMesh("assets/models/fourmis/formica_rufa.obj");
		auto *fourmiTex = Assets::GetTexture("assets/textures/crate1_diffuse.png"); //BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_diffuse.png");
		auto *fourmiMat = new BeerEngine::Graphics::AMaterial(shader);
		fourmiMat->setAlbedo(fourmiTex);
		meshRenderer->setMaterial(fourmiMat);
		fourmi->transform.position = glm::vec3(-3, 0, 10);
		fourmi->transform.scale = glm::vec3(5, 5, 5);
		fourmi->transform.rotation = glm::vec3(0, 0, 0);


//test obj suzanne

	auto suzanne = instantiate<BeerEngine::GameObject>();
	suzanne->name = "suzanne";
	meshRenderer = suzanne->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh("assets/models/Suzanne.obj");
	auto *suzanneTex = Assets::GetTexture("assets/textures/crate1_diffuse.png"); //BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_diffuse.png");
	auto *suzanneMat = new BeerEngine::Graphics::AMaterial(shader);
	suzanneMat->setAlbedo(suzanneTex);
	meshRenderer->setMaterial(suzanneMat);
	suzanne->transform.position = glm::vec3(0, 4, 16);
	suzanne->transform.scale = glm::vec3(1,1,1);
	suzanne->transform.rotation = glm::vec3(0, 0, 0);

	//test obj lightBulb

	auto lightBulb = instantiate<BeerEngine::GameObject>();
	lightBulb->name = "lightBulb";
	meshRenderer = lightBulb->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh("assets/models/lightbulb.obj");
	auto *lightBulbTex = Assets::GetTexture("assets/textures/crate1_diffuse.png"); //BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_diffuse.png");
	auto *lightBulbMat = new BeerEngine::Graphics::AMaterial(shader);
	lightBulbMat->setAlbedo(lightBulbTex);
	meshRenderer->setMaterial(lightBulbMat);
	lightBulb->transform.position = glm::vec3(0, 4, 16);
	lightBulb->transform.scale = glm::vec3(1,1,1);
	lightBulb->transform.rotation = glm::vec3(0, 0, 0);

    //
	// //test obj Orange
    //
	// 	auto Orange = instantiate<BeerEngine::GameObject>();
	// 	Orange->name = "Orange";
	// 	meshRenderer = Orange->AddComponent<BeerEngine::Component::MeshRenderer>();
	// 	meshRenderer->setMesh("assets/models/OrangeOBJ/Orange.obj");
	// 	auto *OrangeTex = BeerEngine::Graphics::Texture::LoadJPG("assets/models/OrangeOBJ/Color.jpg");
	// 	auto *OrangeMat = new BeerEngine::Graphics::AMaterial(shader);
	// 	OrangeMat->setAlbedo(OrangeTex);
	// 	meshRenderer->setMaterial(OrangeMat);
	// 	Orange->transform.position = glm::vec3(0, 7, 10);
	// 	Orange->transform.scale = glm::vec3(1,1,1);
	// 	Orange->transform.rotation = glm::vec3(0, 3, 0);


	// mapBlocs
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-5, 0.5, 6), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-5, 0.5, 8), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-5, 0.5, 10), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-5, 0.5, 12), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-5, 0.5, 14), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-3, 0.5, 14), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-1, 0.5, 14), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(1, 0.5, 14), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(3, 0.5, 14), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(3, 0.5, 12), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(3, 0.5, 10), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(3, 0.5, 8), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(3, 0.5, 6), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(1, 0.5, 6), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-1, 0.5, 6), false);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-3, 0.5, 6), false);

	// Item
	auto itemGO = addCrate<BeerEngine::Component::CircleCollider>(shader, glm::vec3(0.5, 0.5, 0.5), glm::vec3(-3, 0.5, 10), true);
	itemGO->name = "item";
	itemGO->AddComponent<Game::Component::Item>();
	auto itemColl = itemGO->GetComponent<BeerEngine::Component::CircleCollider>();
	itemColl->_isTrigger = true;

	// plane
	BeerEngine::GameObject *mapGO;
	mapGO = instantiate<BeerEngine::GameObject>();
	BeerEngine::Component::MeshRenderer *mapMeshRenderer = mapGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	mapMeshRenderer->setMesh(BeerEngine::Graphics::Graphics::plane);
	mapMeshRenderer->setMaterial(material);
	mapGO->transform.position = glm::vec3(-3, 0, 6);
	mapGO->transform.scale = glm::vec3(40, 1, 40);


	// Particule -1 0.5 10
	BeerEngine::Graphics::ParticlesSystem *particles;
	particles = instantiate<BeerEngine::Graphics::ParticlesSystem>();
	particles->setTexture( Assets::GetTexture("assets/textures/ParticleAtlas.png")); // textures/ParticleAtlas.png
	particles->transform.position = glm::vec3(0, 0.5, 0);
	particles->transform.parent =  &(playerGO->transform);
	// particles->transform.rotation = glm::vec3(0, 1.14f, 0);
	// meshRenderer->setMaterial(materialA);
	// gameObject->transform.position = glm::vec3(-1, 0, 4);
	// gameObject->transform.rotation = glm::quat(glm::vec3(0.0f, glm::radians(45.0f), 0.0f));

	// => GameObject 2 : Cube Mid
	// gameObject = instantiate<BeerEngine::GameObject>();
	// meshRenderer = gameObject->AddComponent<BeerEngine::Component::MeshRenderer>();
	// meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
	// meshRenderer->setMaterial(materialB);
	// gameObject->transform.position = glm::vec3(-1, 1, 4);
	// gameObject->transform.rotation = glm::quat(glm::vec3(0.0f, glm::radians(22.5f), 0.0f));

	// => GameObject 2 : Cube Top
	// gameObject = instantiate<BeerEngine::GameObject>();
	// meshRenderer = gameObject->AddComponent<BeerEngine::Component::MeshRenderer>();
	// meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
	// meshRenderer->setMaterial(materialC);
	// gameObject->transform.position = glm::vec3(-0.5, 2, 4);
	// gameObject->transform.rotation = glm::quat(glm::vec3(0.0f, glm::radians(66.0f), 0.0f));

	// => GameObject 3 : Plane
	// gameObject = instantiate<BeerEngine::GameObject>();
	// meshRenderer = gameObject->AddComponent<BeerEngine::Component::MeshRenderer>();
	// meshRenderer->setMesh(BeerEngine::Graphics::Graphics::plane);
	// meshRenderer->setMaterial(material2);
	// gameObject->transform.position = glm::vec3(0, -0.5, 4);
	// std::cout << "init end" << "\n";

	this->save("test2.scene");
}

