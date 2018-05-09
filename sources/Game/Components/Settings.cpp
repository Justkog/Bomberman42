#include "Game/Components/Settings.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Core/KeyCode.hpp"
#include "Game/Input.hpp"
#include "Core/Window.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

// Game::Component::Settings::Settings ( void )
// {
// 	return ;
// }

// Game::Component::Settings::Settings ( Game::Component::Settings const & src )
// {
// 	*this = src;
// 	return ;
// }

Game::Component::Settings::Settings (BeerEngine::GameObject *gameObject) :
	Component(gameObject)
{
	this->filePath = "testSettings.json";
	return ;
}

Game::Component::Settings &				Game::Component::Settings::operator=( Game::Component::Settings const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Game::Component::Settings::~Settings ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				Game::Component::operator<<(std::ostream & o, Game::Component::Settings const & i)
{
	nlohmann::json j = i.settingsContainer;
	o << j.dump(4);
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

Game::SettingsContainer Game::Component::Settings::defaultSettings()
{
	Game::SettingsContainer settings;

	settings.soundVolume = 50.0f;
	settings.musicVolume = 50.0f;
	settings.windowWidth = 1600;
	settings.windowHeight = 900;
	settings.fullScreen = false;
	settings.keyBindings["move up"] = BeerEngine::KeyCode::W;
	settings.keyBindings["move down"] = BeerEngine::KeyCode::S;
	settings.keyBindings["move left"] = BeerEngine::KeyCode::A;
	settings.keyBindings["move right"] = BeerEngine::KeyCode::D;
	settings.keyBindings["bomb"] = BeerEngine::KeyCode::SPACE;

	return settings;
}

void Game::Component::Settings::loadSettings() {
	std::string content = BeerEngine::IO::FileUtils::LoadFile(this->filePath);
	auto j = nlohmann::json::parse(content);
	this->settingsContainer = j;

	for (auto it = this->settingsContainer.keyBindings.begin(); it != this->settingsContainer.keyBindings.end(); it++)
		Game::Input::keyBindings[it->first] = static_cast<BeerEngine::KeyCode>(this->settingsContainer.keyBindings[it->first]);
	BeerEngine::Window::GetInstance()->resize(this->settingsContainer.windowWidth, this->settingsContainer.windowHeight);
	if (this->settingsContainer.fullScreen)
		BeerEngine::Window::GetInstance()->setFullScreen();
}

void Game::Component::Settings::saveSettings() {
	for (auto it = Game::Input::keyBindings.begin(); it != Game::Input::keyBindings.end(); it++)
		this->settingsContainer.keyBindings[it->first] = static_cast<BeerEngine::KeyCode>(Game::Input::keyBindings[it->first]);
	this->settingsContainer.windowWidth = BeerEngine::Window::GetInstance()->getWindowedWidth();
	this->settingsContainer.windowHeight = BeerEngine::Window::GetInstance()->getWindowedHeight();
	this->settingsContainer.fullScreen = BeerEngine::Window::GetInstance()->isFullScreen();

	nlohmann::json j = this->settingsContainer;
	std::string content = j.dump(4);
	BeerEngine::IO::FileUtils::WriteFile(this->filePath, content);
	// std::cout << content << std::endl;
}

void    Game::Component::Settings::start(void) {
	this->loadSettings();
	// std::cout << "Settings: " << "\n" << *this << "\n";
	// this->saveSettings();
}

nlohmann::json	Game::Component::Settings::serialize()
{
	return nlohmann::json {
		{"componentClass", typeid(Game::Component::Settings).name()},
		{"filePath", filePath},
	};
}

void Game::Component::Settings::deserialize(const nlohmann::json & j)
{
	
}

REGISTER_COMPONENT_CPP(Game::Component::Settings)

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

namespace Game {
    void to_json(nlohmann::json& j, const Game::SettingsContainer& s) {
        j = nlohmann::json {
			{"soundVolume", s.soundVolume},
			{"musicVolume", s.musicVolume},
			{"windowWidth", s.windowWidth},
			{"windowHeight", s.windowHeight},
			{"fullScreen", s.fullScreen},
			{"keyBindings", s.keyBindings},
			{"unlockedLevels", s.unlockedLevels},
			// {"stringSetting", s.stringSetting},
			// {"intSetting", s.intSetting},
			// {"listSettings", s.listSettings},
		};
    }

    void from_json(const nlohmann::json& j, Game::SettingsContainer& s) {
		s = Game::Component::Settings::defaultSettings();
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
		if (j.find("unlockedLevels") != j.end())
	        s.unlockedLevels = j.at("unlockedLevels").get<std::vector<std::string>>();
		// s.stringSetting = j.at("stringSetting").get<std::string>();
		// s.intSetting = j.at("intSetting").get<int>();
		// s.listSettings = j.at("listSettings").get<std::vector<std::string>>();
    }
}

// ###############################################################
