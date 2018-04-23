#include "Game/SceneTest.hpp"

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
	// Material
	BeerEngine::Graphics::AMaterial *material = new BeerEngine::Graphics::AMaterial(shader);
	BeerEngine::Graphics::AMaterial *material2 = new BeerEngine::Graphics::AMaterial(shader);
	material2->setColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
	// Camera
	BeerEngine::Camera::main->transform.position = glm::vec3(-1, 1, 0);
	BeerEngine::Camera::main->transform.rotation = glm::quat(glm::vec3(0.0f, glm::radians(22.5f), 0.0f));
	// GameObject
	BeerEngine::GameObject *gameObject;
	// => GameObject 1
	gameObject = instantiate<BeerEngine::GameObject>();
	BeerEngine::Component::MeshRenderer *meshRenderer = gameObject->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
	meshRenderer->setMaterial(material);
	gameObject->transform.position = glm::vec3(-1, 0, 4);
	gameObject->transform.rotation = glm::quat(glm::vec3(0.0f, glm::radians(45.0f), 0.0f));
	// => GameObject 2
	gameObject = instantiate<BeerEngine::GameObject>();
	meshRenderer = gameObject->AddComponent<BeerEngine::Component::MeshRenderer>();
	meshRenderer->setMesh(BeerEngine::Graphics::Graphics::plane);
	meshRenderer->setMaterial(material2);
	gameObject->transform.position = glm::vec3(0, -0.5, 4);
}