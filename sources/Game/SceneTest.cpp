#include "Game/SceneTest.hpp"
#include "Game/Components/Settings.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Game/Components/Player.hpp"
#include "Game/Components/Item.hpp"
#include "Game/Components/CameraController.hpp"
#include "Game/CameraTest.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Json/Json.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/ShaderProgram.hpp"

template<typename T>
BeerEngine::GameObject *SceneTest::addCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, bool kinematic)
{
	BeerEngine::Component::MeshRenderer *meshRenderer;
	auto mapBlocGO = instantiate<BeerEngine::GameObject>();
	mapBlocGO->name = "map block";
	meshRenderer = mapBlocGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
	auto *mapBlocTex = BeerEngine::Graphics::Texture::LoadPNG("textures/crate1_diffuse.png");
	auto *mapBlocMat = new BeerEngine::Graphics::AMaterial(shader);
	mapBlocMat->setAlbedo(mapBlocTex);
	meshRenderer->setMaterial(mapBlocMat);
	mapBlocGO->transform.position = pos;
	mapBlocGO->transform.scale = scale;
	auto blockColl = mapBlocGO->AddComponent<T>();
	blockColl->_kinematic = kinematic;

	return (mapBlocGO);
}

void    SceneTest::init(void)
{
	this->load("test.scene");
	this->save("destest.scene");
	
	return;

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
	BeerEngine::Graphics::Texture *crate = BeerEngine::Graphics::Texture::LoadPNG("textures/crate1_diffuse.png");
	BeerEngine::Graphics::Texture *crate_normal = BeerEngine::Graphics::Texture::LoadPNG("textures/crate1_normal.png");
	BeerEngine::Graphics::Texture *crate_bump = BeerEngine::Graphics::Texture::LoadPNG("textures/crate1_bump.png");

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
	auto *playerTex = BeerEngine::Graphics::Texture::LoadPNG("textures/player2.png");
	auto *playerMat = new BeerEngine::Graphics::AMaterial(shader);
	playerMat->setAlbedo(playerTex);
	meshRenderer->setMaterial(playerMat);
	playerGO->transform.position = glm::vec3(1, 0.5, 7);
	playerGO->transform.scale = glm::vec3(1, 1, 1);
	auto *player = playerGO->AddComponent<Game::Component::Player>();
	auto *settings = playerGO->AddComponent<Game::Component::Settings>();
	auto playerColl = playerGO->AddComponent<BeerEngine::Component::BoxCollider2D>();
	playerColl->_kinematic = false;

//test obj house

	auto objet = instantiate<BeerEngine::GameObject>();
	objet->name = "house";
	meshRenderer = objet->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh("models/house_01.obj");
	auto *objetTex = BeerEngine::Graphics::Texture::LoadPNG("textures/crate1_diffuse.png");
	auto *objetMat = new BeerEngine::Graphics::AMaterial(shader);
	objetMat->setAlbedo(objetTex);
	meshRenderer->setMaterial(objetMat);
	objet->transform.position = glm::vec3(7, 0.5, 10);
	objet->transform.scale = glm::vec3(0.05, 0.05, 0.05);
	objet->transform.rotation = glm::vec3(0, -1.5, 0);


//test obj car

	auto car = instantiate<BeerEngine::GameObject>();
	car->name = "car";
	meshRenderer = car->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh("models/Dodge_Chellenger_SRT10_OBJ.obj");
	auto *carTex = BeerEngine::Graphics::Texture::LoadPNG("textures/crate1_diffuse.png");
	auto *carMat = new BeerEngine::Graphics::AMaterial(shader);
	carMat->setAlbedo(carTex);
	meshRenderer->setMaterial(carMat);
	car->transform.position = glm::vec3(0, 0.5, 10);
	car->transform.scale = glm::vec3(0.02, 0.02, 0.02);
	car->transform.rotation = glm::vec3(0, -1.5, 0);

//test obj bigmax

	auto bigmax = instantiate<BeerEngine::GameObject>();
	bigmax->name = "bigmax";
	meshRenderer = bigmax->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh("models/Bigmax_White_OBJ.obj");
	auto *bigmaxTex = BeerEngine::Graphics::Texture::LoadPNG("textures/crate1_diffuse.png");
	auto *bigmaxMat = new BeerEngine::Graphics::AMaterial(shader);
	bigmaxMat->setAlbedo(bigmaxTex);
	meshRenderer->setMaterial(bigmaxMat);
	bigmax->transform.position = glm::vec3(-7, 0, 10);
	bigmax->transform.scale = glm::vec3(0.07, 0.07, 0.07);
	bigmax->transform.rotation = glm::vec3(0, 3, 0);

//test obj suzanne

	auto suzanne = instantiate<BeerEngine::GameObject>();
	suzanne->name = "suzanne";
	meshRenderer = suzanne->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh("models/Suzanne.obj");
	auto *suzanneTex = BeerEngine::Graphics::Texture::LoadPNG("textures/crate1_diffuse.png");
	auto *suzanneMat = new BeerEngine::Graphics::AMaterial(shader);
	suzanneMat->setAlbedo(suzanneTex);
	meshRenderer->setMaterial(suzanneMat);
	suzanne->transform.position = glm::vec3(0, 4, 16);
	suzanne->transform.scale = glm::vec3(1,1,1);
	suzanne->transform.rotation = glm::vec3(0, 3, 0);

	// //test obj Suzanne
    //
	//  	inputfile = "models/Suzanne.obj";
	// 	auto Suobjet = instantiate<BeerEngine::GameObject>();
	// 	Suobjet->name = "Suzanne";
	// 	meshRenderer = Suobjet->AddComponent<BeerEngine::Component::MeshRenderer>();
	// 	BeerEngine::Graphics::MeshBuilder Subuilder;
    //
	// 	ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());
    //
	// 	if (!err.empty()) // `err` may contain warning message.
	// 	  std::cerr << err << std::endl;
    //
	// 	if (!ret)
	// 	  exit(1);
    //
	// 	// Loop over shapes
	// 	for (size_t s = 0; s < shapes.size(); s++)
	// 	{
	// 	  // Loop over faces(polygon)
	// 	  size_t index_offset = 0;
	// 	  for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
	// 	  {
	// 	    int fv = shapes[s].mesh.num_face_vertices[f];
	// 	    // Loop over vertices in the face.
	// 	    for (size_t v = 0; v < fv; v++)
	// 		{
	// 	      // access to vertex
	// 	      tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
	// 	      tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
	// 	      tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
	// 	      tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
	// 		  // std::cout << "on est la 7.4" << std::endl;
	// 	      tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
	// 		  // std::cout << "on est la 7.5" << std::endl;
	// 	      tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
	// 		  // std::cout << "on est la 7.6" << std::endl;
	// 	      tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
	// 	      tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
	// 	      tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];
    //
	// 		  Subuilder
	// 			  .addVertice(glm::vec3(vx, vy, vz))
	// 			  .addNormal(glm::vec3(nx, ny, nz))
	// 			  .addUV(glm::vec2(tx, ty))
	// 		 ;
	// 	      // Optional: vertex colors
	// 	      // tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
	// 	      // tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
	// 	      // tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
	// 	    }
	// 	    index_offset += fv;
	// 	    // per-face material
	// 	    shapes[s].mesh.material_ids[f];
	// 	  }
	// 	}
	// 	builder.calculTangent();
    //
	// 	meshRenderer->setMesh(Subuilder.build());
	// 	objetTex = BeerEngine::Graphics::Texture::LoadPNG("textures/crate1_diffuse.png");
	// 	objetMat = new BeerEngine::Graphics::AMaterial(shader);
	// 	objetMat->setAlbedo(objetTex);
	// 	meshRenderer->setMaterial(objetMat);
	// 	Suobjet->transform.position = glm::vec3(4, 0.5, 18);
	// 	Suobjet->transform.scale = glm::vec3(1, 1, 1);
	// 	Suobjet->transform.rotation = glm::vec3(-0.3, 3.14, 0);
    //


	// mapBlocs
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-5, 0.5, 6), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-5, 0.5, 8), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-5, 0.5, 10), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-5, 0.5, 12), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-5, 0.5, 14), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-3, 0.5, 14), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-1, 0.5, 14), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(1, 0.5, 14), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(3, 0.5, 14), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(3, 0.5, 12), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(3, 0.5, 10), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(3, 0.5, 8), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(3, 0.5, 6), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(1, 0.5, 6), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-1, 0.5, 6), true);
	addCrate<BeerEngine::Component::BoxCollider2D>(shader, glm::vec3(1, 1, 1), glm::vec3(-3, 0.5, 6), true);

	// Item
	auto itemGO = addCrate<BeerEngine::Component::CircleCollider>(shader, glm::vec3(0.5, 0.5, 0.5), glm::vec3(-3, 0.5, 10), true);
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

	this->save("test.scene");
}

