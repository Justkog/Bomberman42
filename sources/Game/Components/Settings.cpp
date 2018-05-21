#include "Game/Components/Settings.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Core/KeyCode.hpp"
#include "Game/Input.hpp"
#include "Core/Window.hpp"
#include "Game/Components/AudioManager.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

Settings * Settings::instance = nullptr;

Settings & Settings::GetInstance()
{
	return *Settings::instance;
}

// ###############################################################

// CANONICAL #####################################################

Settings::Settings ( void )
{
	return ;
}

Settings::Settings ( Settings const & src )
{
	*this = src;
	return ;
}

Settings &	Settings::operator=( Settings const & rhs )
{
	(void) rhs;
	if (this != &rhs)
	{}
	return (*this);
}

Settings::Settings (BeerEngine::GameObject *gameObject) :
	Component(gameObject),
	audioManager(nullptr)
{
	this->filePath = "testSettings.json";
	instance = this;
}

Settings::~Settings ( void )
{

}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, Settings const & i)
{
	nlohmann::json j = i.settingsContainer;
	o << j.dump(4);
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

Game::SettingsContainer Settings::defaultSettings()
{
	Game::SettingsContainer settings;
	settings.soundVolume = 50.0f;
	settings.musicVolume = 50.0f;
	settings.windowWidth = 1600;
	settings.windowHeight = 900;
	settings.fullScreen = false;
	settings.keyBindings["move up"] = BeerEngine::KeyCode::KP_8;
	settings.keyBindings["move down"] = BeerEngine::KeyCode::KP_5;
	settings.keyBindings["move left"] = BeerEngine::KeyCode::KP_4;
	settings.keyBindings["move right"] = BeerEngine::KeyCode::KP_6;
	settings.keyBindings["bomb"] = BeerEngine::KeyCode::SPACE;
	settings.keyBindings["change view"] = BeerEngine::KeyCode::W;
	// settings.unlockedLevels = { "Level1" };

	return settings;
}

void Settings::applyCurrentSettings() {
	for (auto it = this->settingsContainer.keyBindings.begin(); it != this->settingsContainer.keyBindings.end(); it++)
		Game::Input::keyBindings[it->first] = static_cast<BeerEngine::KeyCode>(this->settingsContainer.keyBindings[it->first]);
	BeerEngine::Window::GetInstance()->resize(this->settingsContainer.windowWidth, this->settingsContainer.windowHeight);
	if (this->settingsContainer.fullScreen)
		BeerEngine::Window::GetInstance()->setFullScreen();
	else
		BeerEngine::Window::GetInstance()->setWindowed();
	if (audioManager)
	{
		std::cout << "================================applying sound settings" << std::endl;
		this->audioManager->setVolume(this->settingsContainer.soundVolume / 100, this->settingsContainer.musicVolume / 100);
	}
}

void Settings::gatherCurrentSettings() {
	for (auto it = Game::Input::keyBindings.begin(); it != Game::Input::keyBindings.end(); it++)
		this->settingsContainer.keyBindings[it->first] = static_cast<BeerEngine::KeyCode>(Game::Input::keyBindings[it->first]);
	this->settingsContainer.windowWidth = BeerEngine::Window::GetInstance()->getWindowedWidth();
	this->settingsContainer.windowHeight = BeerEngine::Window::GetInstance()->getWindowedHeight();
	this->settingsContainer.fullScreen = BeerEngine::Window::GetInstance()->isFullScreen();
	if (audioManager)
	{
		this->settingsContainer.soundVolume = audioManager->getSoundVolume() * 100;
		this->settingsContainer.musicVolume = audioManager->getMusicVolume() * 100;
	}
}

void Settings::loadSettings() {
	std::string content = BeerEngine::IO::FileUtils::LoadFile(this->filePath);
	nlohmann::json j;
	if (content != "")
	{
		try
		{
			j = nlohmann::json::parse(content);
		}
		catch(const std::exception& e)
		{
			j = {};
		}
	}
	else
		j = {};	
	this->settingsContainer = j;
	this->applyCurrentSettings();
}

void Settings::saveSettings() {
	this->gatherCurrentSettings();

	nlohmann::json j = this->settingsContainer;
	std::string content = j.dump(4);
	BeerEngine::IO::FileUtils::WriteFile(this->filePath, content);
	// std::cout << content << std::endl;
}

void Settings::resetSettings() {
	this->settingsContainer = Settings::defaultSettings();
	this->applyCurrentSettings();

	nlohmann::json j = this->settingsContainer;
	std::string content = j.dump(4);
	BeerEngine::IO::FileUtils::WriteFile(this->filePath, content);
}

void    Settings::start(void) {
	this->loadSettings();
	// std::cout << "Settings: " << "\n" << *this << "\n";
}

nlohmann::json	Settings::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
		{"filePath", filePath},
	});
	return j;
}

void Settings::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
	this->filePath = j.at("filePath");
}

REGISTER_COMPONENT_CPP(Settings)

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
	}
}

namespace Game {
    void to_json(nlohmann::json& j, const Game::SettingsContainer& s) {
        j = nlohmann::json {
			{"soundVolume", s.soundVolume},
			{"musicVolume", s.musicVolume},
			{"windowWidth", s.windowWidth},
			{"windowHeight", s.windowHeight},
			{"fullScreen", s.fullScreen},
			{"keyBindings", s.keyBindings},
		};
    }

    void from_json(const nlohmann::json& j, Game::SettingsContainer& s) {
		s = Component::Settings::defaultSettings();
		try
		{
			if (j.find("soundVolume") != j.end())
				s.soundVolume = j.at("soundVolume").get<float>();
			if (j.find("musicVolume") != j.end())
				s.musicVolume = j.at("musicVolume").get<float>();
			if (j.find("windowWidth") != j.end())
				s.windowWidth = j.at("windowWidth").get<int>();
			if (j.find("windowHeight") != j.end())
				s.windowHeight = j.at("windowHeight").get<int>();
			if (j.find("fullScreen") != j.end())
				s.fullScreen = j.at("fullScreen").get<bool>();
			if (j.find("keyBindings") != j.end())
				s.keyBindings = j.at("keyBindings").get<std::map<std::string, int>>();
		}
		catch (const std::exception& e)
		{

		}
		// for (auto it = s.keyBindings.begin(); it != s.keyBindings.end(); it++)
		// 	std::cout << "loaded key " << it->first << " / " << it->second << std::endl;
    }
}
