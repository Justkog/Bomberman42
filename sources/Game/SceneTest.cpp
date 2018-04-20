#include "Game/SceneTest.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Game/Components/Player.hpp"
#include "Game/Components/CameraController.hpp"

void    SceneTest::init(void)
{
	BeerEngine::Graphics::ShaderProgram *shader = new BeerEngine::Graphics::ShaderProgram(2);
	shader->load(0, GL_VERTEX_SHADER, 
		BeerEngine::IO::FileUtils::LoadFile("shaders/basic_v.glsl").c_str()
	);
	shader->load(1, GL_FRAGMENT_SHADER, 
		BeerEngine::IO::FileUtils::LoadFile("shaders/basic_f.glsl").c_str()
	);
	shader->compile();
	BeerEngine::Graphics::AMaterial *material = new BeerEngine::Graphics::AMaterial(shader);

	// Camera
	BeerEngine::GameObject *cameraGO;
	cameraGO = instantiate<BeerEngine::GameObject>();
	Game::Component::CameraController *cameraController = cameraGO->AddComponent<Game::Component::CameraController>();

	// cube 1
	BeerEngine::GameObject *gameObject;
	gameObject = instantiate<BeerEngine::GameObject>();
	BeerEngine::Component::MeshRenderer *meshRenderer = gameObject->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
	meshRenderer->setMaterial(material);
	gameObject->transform.position = glm::vec3(-3, -2, 6);
	gameObject->transform.scale = glm::vec3(1, 1, 1);

	Game::Component::Player *player = gameObject->AddComponent<Game::Component::Player>();

	// plane
	BeerEngine::GameObject *mapGO;
	mapGO = instantiate<BeerEngine::GameObject>();
	BeerEngine::Component::MeshRenderer *mapMeshRenderer = mapGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	mapMeshRenderer->setMesh(BeerEngine::Graphics::Graphics::plane);
	mapMeshRenderer->setMaterial(material);
	mapGO->transform.position = glm::vec3(-3, -3, 6);
	mapGO->transform.scale = glm::vec3(40, 1, 40);

	
}