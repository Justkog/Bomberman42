#include "Game/SceneTest.hpp"
#include "Game/SceneMain.hpp"
#include "Game/Components/Settings.hpp"
#include "Game/Components/GameProgression.hpp"
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
#include "Game/Components/VersusMenu.hpp"
#include "Game/Components/AdventureMenu.hpp"
#include "Game/Components/AdventureContinueMenu.hpp"
#include "Game/Components/SettingsMenu.hpp"
#include "Game/Components/InputsMenu.hpp"
#include "Game/Components/Credits.hpp"
#include "Game/Components/BackgroundDrawer.hpp"
#include "Game/Components/UIThemeManager.hpp"

#include "Game/Components/CameraController.hpp"
#include "Game/Components/AudioManager.hpp"
#include "Game/Components/MouseRayTest.hpp"
#include "Game/Components/BeerRoutineTester.hpp"
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

	// Camera
	auto cameraGO = instantiate<BeerEngine::GameObject>();
	cameraGO->name = "Camera";

	cameraGO->AddComponent<Game::Component::CameraController>();

	auto menuGO = instantiate<BeerEngine::GameObject>();
	auto settings = menuGO->AddComponent<Game::Component::Settings>();
	auto gameProgression = menuGO->AddComponent<Game::Component::GameProgression>();
	auto uiManager = menuGO->AddComponent<Game::Component::UIThemeManager>();
	auto bgDrawer = menuGO->AddComponent<Game::Component::BackgroundDrawer>();
	auto mainMenu = menuGO->AddComponent<Game::Component::MainMenu>();
	auto adventureMenu = menuGO->AddComponent<Game::Component::AdventureMenu>();
	auto adventureContinueMenu = menuGO->AddComponent<Game::Component::AdventureContinueMenu>();
	auto versusMenu = menuGO->AddComponent<Game::Component::VersusMenu>();
	auto settingsMenu = menuGO->AddComponent<Game::Component::SettingsMenu>();
	auto inputsMenu = menuGO->AddComponent<Game::Component::InputsMenu>();
	auto credits = menuGO->AddComponent<Game::Component::Credits>();
	auto audioManager = menuGO->AddComponent<Game::Component::AudioManager>();

	bgDrawer->uiManager = uiManager;
	mainMenu->uiManager = uiManager;
	versusMenu->uiManager = uiManager;
	adventureMenu->uiManager = uiManager;
	adventureContinueMenu->uiManager = uiManager;
	settingsMenu->uiManager = uiManager;
	inputsMenu->uiManager = uiManager;
	credits->uiManager = uiManager;

	mainMenu->adventureMenu = adventureMenu;
	mainMenu->versusMenu = versusMenu;
	mainMenu->settingsMenu = settingsMenu;
	mainMenu->credits = credits;
	versusMenu->mainMenu = mainMenu;
	adventureMenu->mainMenu = mainMenu;
	adventureMenu->continueMenu = adventureContinueMenu;
	adventureMenu->gameProgression = gameProgression;
	adventureContinueMenu->adventureMenu = adventureMenu;
	adventureContinueMenu->gameProgression = gameProgression;
	settingsMenu->mainMenu = mainMenu;
	settingsMenu->inputsMenu = inputsMenu;
	settingsMenu->settingsManager = settings;
	settingsMenu->audioManager = audioManager;
	inputsMenu->settingsMenu = settingsMenu;
	credits->mainMenu = mainMenu;
	
	settings->audioManager = audioManager;

// init musique du menu
	audioManager->setClip("assets/sounds/Feel.ogg");
	audioManager->audioType = Game::Component::Music;

	// mainMenu->setActive(false);
	versusMenu->setActive(false);
	settingsMenu->setActive(false);
	inputsMenu->setActive(false);
	adventureMenu->setActive(false);
	adventureContinueMenu->setActive(false);
	credits->setActive(false);

	this->save("assets/scenes/main.scene");
	std::cout << "init end" << "\n";
}
