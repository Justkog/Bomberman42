#include "Game/Components/Settings.hpp"
#include "Core/IO/FileUtils.hpp"

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

void Game::Component::Settings::loadSettings() {
	std::string content = BeerEngine::IO::FileUtils::LoadFile(this->filePath);
	auto j = nlohmann::json::parse(content);
	// Game::SettingsContainer c;
	this->settingsContainer = j;
}

void Game::Component::Settings::saveSettings() {
	nlohmann::json j = this->settingsContainer;
	std::string content = j.dump(4);
	BeerEngine::IO::FileUtils::WriteFile(this->filePath, content);
	std::cout << content << std::endl;
}

void    Game::Component::Settings::start(void) {
	// this->settingsContainer.soundVolume = 0.5f;
	// this->settingsContainer.stringSetting = "some setting";
	// this->settingsContainer.intSetting = 42;
	// this->settingsContainer.listSettings.push_back("one setting");
	// this->settingsContainer.listSettings.push_back("another setting");
	this->loadSettings();
	std::cout << "Settings: " << "\n" << *this << "\n";
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
			{"stringSetting", s.stringSetting},
			{"intSetting", s.intSetting},
			{"listSettings", s.listSettings},
		};
    }

    void from_json(const nlohmann::json& j, Game::SettingsContainer& s) {
        s.soundVolume = j.at("soundVolume").get<float>();
		s.stringSetting = j.at("stringSetting").get<std::string>();
		s.intSetting = j.at("intSetting").get<int>();
		s.listSettings = j.at("listSettings").get<std::vector<std::string>>();
    }
}

// ###############################################################
