#include "Game/SceneLoader.hpp"
#include "Core/SceneManager.hpp"
#include "Game/SceneTest.hpp"
#include "Game/SceneMain.hpp"
#include "Core/SceneManager.hpp"
#include "Game/Level1.hpp"
#include "Game/Level2.hpp"
#include "Game/Level3.hpp"
#include "Game/Level4.hpp"

namespace Game
{
	std::map<std::string, LoadScene> SceneLoader::nameToLoad = {
		{"SceneMain", BeerEngine::SceneManager::LoadScene<SceneMain>},
		{"Level1", BeerEngine::SceneManager::LoadScene<Level1>},
		{"Level2", BeerEngine::SceneManager::LoadScene<Level2>},
		{"Level3", BeerEngine::SceneManager::LoadScene<Level3>},
		{"Level4", BeerEngine::SceneManager::LoadScene<Level4>},
	};

	void SceneLoader::loadByName(std::string name)
	{
		auto load = nameToLoad.find(name);
		if (load != nameToLoad.end())
			nameToLoad[name]();
		else
			std::cout << "no matching scene!" << std::endl;
	}

	void SceneLoader::load()
	{
		loadByName(name);
	}
}