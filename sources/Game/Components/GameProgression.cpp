#include "Game/Components/GameProgression.hpp"
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

GameProgression * GameProgression::instance = nullptr;

GameProgression & GameProgression::GetInstance()
{
	return *GameProgression::instance;
}

// ###############################################################

// CANONICAL #####################################################

// GameProgression::GameProgression ( void )
// {
// 	return ;
// }

// GameProgression::GameProgression ( GameProgression const & src )
// {
// 	*this = src;
// 	return ;
// }

GameProgression::GameProgression (BeerEngine::GameObject *gameObject) :
	Component(gameObject),
	audioManager(nullptr)
{
	this->filePath = "GameProgression.json";
	instance = this;
}

GameProgression &				GameProgression::operator=( GameProgression const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

GameProgression::~GameProgression ( void )
{

}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, GameProgression const & i)
{
	nlohmann::json j = i.gameProgressionContainer;
	o << j.dump(4);
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

Game::GameProgressionContainer GameProgression::defaultGameProgression()
{
	Game::GameProgressionContainer gameProgression;
	
	gameProgression.unlockedLevels = { "Level1" };

	return gameProgression;
}

void GameProgression::applyCurrentGameProgression() {
	
}

void GameProgression::gatherCurrentGameProgression() {
	
}

void GameProgression::loadGameProgression() {
	std::string content = BeerEngine::IO::FileUtils::LoadFile(this->filePath);
	nlohmann::json j;
	if (content != "")
		j = nlohmann::json::parse(content);
	else
		j = {};	
	this->gameProgressionContainer = j;
	this->applyCurrentGameProgression();
}

void GameProgression::saveGameProgression() {
	this->gatherCurrentGameProgression();

	nlohmann::json j = this->gameProgressionContainer;
	std::string content = j.dump(4);
	BeerEngine::IO::FileUtils::WriteFile(this->filePath, content);
	// std::cout << content << std::endl;
}

void GameProgression::resetGameProgression() {
	this->gameProgressionContainer = GameProgression::defaultGameProgression();
	this->applyCurrentGameProgression();

	nlohmann::json j = this->gameProgressionContainer;
	std::string content = j.dump(4);
	BeerEngine::IO::FileUtils::WriteFile(this->filePath, content);
}

void    GameProgression::start(void) {
	this->loadGameProgression();
	// std::cout << "GameProgression: " << "\n" << *this << "\n";
}

nlohmann::json	GameProgression::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
		{"filePath", filePath},
	});
	return j;
}

void GameProgression::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
	this->filePath = j.at("filePath");
}

REGISTER_COMPONENT_CPP(GameProgression)

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
    void to_json(nlohmann::json& j, const Game::GameProgressionContainer& s) {
        j = nlohmann::json {
			{"unlockedLevels", s.unlockedLevels},
		};
    }

    void from_json(const nlohmann::json& j, Game::GameProgressionContainer& s) {
		s = Component::GameProgression::defaultGameProgression();
		if (j.find("unlockedLevels") != j.end())
	        s.unlockedLevels = j.at("unlockedLevels").get<std::vector<std::string>>();

		// for (auto it = s.keyBindings.begin(); it != s.keyBindings.end(); it++)
		// 	std::cout << "loaded key " << it->first << " / " << it->second << std::endl;
    }
}
