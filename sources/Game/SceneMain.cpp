#include "Game/SceneTest.hpp"
#include "Game/SceneMain.hpp"
#include "Game/Components/Settings.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Core/Component/BoxCollider2D.hpp"
#include "Core/Component/CircleCollider.hpp"
#include "Core/Component/RigidBody2D.hpp"
#include "Core/Component/RaysRenderer.hpp"
#include "Core/Component/ParticleBase.hpp"
#include "Core/Component/ParticleExplode.hpp"
#include "Game/Components/Player.hpp"
#include "Game/Components/IA.hpp"
#include "Game/Components/Character.hpp"
#include "Game/Components/Item.hpp"
#include "Game/Components/Map.hpp"
#include "Game/Components/MainMenu.hpp"
#include "Game/Components/SettingsMenu.hpp"
#include "Game/Components/InputsMenu.hpp"
#include "Game/Components/BackgroundDrawer.hpp"
#include "Game/Components/UIThemeManager.hpp"

#include "Game/Components/CameraController.hpp"
#include "Game/Components/MouseRayTest.hpp"
#include "Game/Components/BeerRoutineTester.hpp"
#include "Game/CameraTest.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Json/Json.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/ShaderProgram.hpp"
#include "Game/Assets.hpp"

void    SceneMain::init(void)
{
	// this->load("test2.scene");
	// this->save("destest.scene");


	// return;

	std::cout << "init main scene" << "\n";

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
	
	// Camera
	BeerEngine::GameObject *cameraGO;
	cameraGO = instantiate<BeerEngine::GameObject>();
	cameraGO->name = "Camera";

	Game::Component::CameraController *cameraController = cameraGO->AddComponent<Game::Component::CameraController>();

	// plane
	BeerEngine::GameObject *bkgdGO;
	bkgdGO = instantiate<BeerEngine::GameObject>();
	BeerEngine::Component::MeshRenderer *bkgdMeshRenderer = bkgdGO->AddComponent<BeerEngine::Component::MeshRenderer>();
	bkgdMeshRenderer->setMesh(BeerEngine::Graphics::Graphics::plane);
	bkgdMeshRenderer->setMaterial(material);
	bkgdGO->transform.position = glm::vec3(-3, 0, 6);
	bkgdGO->transform.scale = glm::vec3(40, 1, 40);

	auto menuGO = instantiate<BeerEngine::GameObject>();
	auto uiManager = menuGO->AddComponent<Game::Component::UIThemeManager>();
	auto bgDrawer = menuGO->AddComponent<Game::Component::BackgroundDrawer>();
	auto mainMenu = menuGO->AddComponent<Game::Component::MainMenu>();
	auto settingsMenu = menuGO->AddComponent<Game::Component::SettingsMenu>();
	auto inputsMenu = menuGO->AddComponent<Game::Component::InputsMenu>();
	bgDrawer->uiManager = uiManager;
	mainMenu->uiManager = uiManager;
	mainMenu->settingsMenu = settingsMenu;
	settingsMenu->uiManager = uiManager;
	settingsMenu->mainMenu = mainMenu;
	settingsMenu->inputsMenu = inputsMenu;
	inputsMenu->uiManager = uiManager;
	inputsMenu->settingsMenu = settingsMenu;
	settingsMenu->setActive(false);
	// mainMenu->setActive(false);
	inputsMenu->setActive(false);

	this->save("main.scene");
	std::cout << "init end" << "\n";
}
