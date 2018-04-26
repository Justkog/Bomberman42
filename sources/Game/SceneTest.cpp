#include "Game/SceneTest.hpp"
#include "Game/Components/Settings.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Game/Components/Player.hpp"
#include "Game/Components/CameraController.hpp"
#include "Game/CameraTest.hpp"

void    SceneTest::init(void)
{
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
	material2->setColor(BeerEngine::Maths::Vector4f(0.5f, 0.0f, 0.0f, 1.0f));
	// material2->setAlbedo(crate);

	// Camera
	BeerEngine::GameObject *cameraGO;
	cameraGO = instantiate<BeerEngine::GameObject>();

	Game::Component::CameraController *cameraController = cameraGO->AddComponent<Game::Component::CameraController>();

	BeerEngine::Camera::main->transform.position = BeerEngine::Maths::Vector3f(0, 1, -5);
	// BeerEngine::Camera::main->transform.rotation = glm::quat(BeerEngine::Maths::Vector3f(glm::radians(0.0f), glm::radians(45.0f), 0.0f));
	/*BeerEngine::Maths::Vector3f v = BeerEngine::Camera::main->transform.forward();
	BeerEngine::Camera::main->transform.translate(-v);*/

	// GameObject
	//
	BeerEngine::GameObject *gameObject;
	BeerEngine::Component::MeshRenderer *meshRenderer;
	
	// FPS Camera
	// instantiate<CameraTest>();
	
	// => GameObject 1
	gameObject = instantiate<BeerEngine::GameObject>();
	meshRenderer = gameObject->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
	meshRenderer->setMaterial(material);
	gameObject->transform.position = BeerEngine::Maths::Vector3f(-3, -2, 6);

	meshRenderer->setMaterial(materialA);
	gameObject->transform.position = BeerEngine::Maths::Vector3f(-1, 0, 4);
	gameObject->transform.rotation.set(0.0f, M_TORADIANS(66.0f), 0.0f);
	// gameObject->transform.scale = BeerEngine::Maths::Vector3f(1, 1, 1);

	// Game::Component::Player *player = gameObject->AddComponent<Game::Component::Player>();
	// Game::Component::Settings *settings = gameObject->AddComponent<Game::Component::Settings>();

	// plane
	BeerEngine::GameObject *mapGO;
	mapGO = instantiate<BeerEngine::GameObject>();
	BeerEngine::Component::MeshRenderer *mapMeshRenderer = mapGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	mapMeshRenderer->setMesh(BeerEngine::Graphics::Graphics::plane);
	mapMeshRenderer->setMaterial(material);
	mapGO->transform.position = BeerEngine::Maths::Vector3f(0, -3, 4);
	mapGO->transform.scale = BeerEngine::Maths::Vector3f(40, 1, 40);

	// gameObject->transform.rotation = glm::quat(BeerEngine::Maths::Vector3f(0.0f, glm::radians(45.0f), 0.0f));

	// => GameObject 2 : Cube Mid
	gameObject = instantiate<BeerEngine::GameObject>();
	meshRenderer = gameObject->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
	meshRenderer->setMaterial(materialB);
	gameObject->transform.position = BeerEngine::Maths::Vector3f(-1, 1, 4);
	gameObject->transform.rotation.set(0.0f, M_TORADIANS(45.0f), 0.0f);
	// gameObject->transform.rotation = glm::quat(BeerEngine::Maths::Vector3f(0.0f, glm::radians(22.5f), 0.0f));
	
	// => GameObject 2 : Cube Top
	gameObject = instantiate<BeerEngine::GameObject>();
	meshRenderer = gameObject->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
	meshRenderer->setMaterial(materialC);
	gameObject->transform.position = BeerEngine::Maths::Vector3f(-1, 2, 4);
	gameObject->transform.rotation.set(0.0f, M_TORADIANS(22.5f), 0.0f);
	// gameObject->transform.rotation = glm::quat(BeerEngine::Maths::Vector3f(0.0f, glm::radians(66.0f), 0.0f));

	// => GameObject 3 : Plane
	gameObject = instantiate<BeerEngine::GameObject>();
	meshRenderer = gameObject->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh(BeerEngine::Graphics::Graphics::plane);
	meshRenderer->setMaterial(material2);
	gameObject->transform.position = BeerEngine::Maths::Vector3f(0, -0.5, 4);
	std::cout << "init end" << "\n";
	
}
