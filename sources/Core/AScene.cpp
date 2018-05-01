#include "Core/AScene.hpp"
#include "Core/Core.hpp"
#include "Core/GameObject.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/MeshRenderer.hpp"
#include "Core/Graphics/Mesh.hpp"
#include "Core/Graphics/MeshBuilder.hpp"
#include "Core/Graphics/ShaderProgram.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Core/Json/Json.hpp"

namespace BeerEngine
{
    int     AScene::uniqueID = 0;

    AScene::AScene(void)
    {
        
    }

    AScene::~AScene(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            delete (it->second);
        }
        _gameObjects.clear();
    }

    std::vector<GameObject *> AScene::getGameObjects()
    {
        std::vector<GameObject *> res;

        // populate map somehow
        for(auto it = _gameObjects.begin(); it != _gameObjects.end(); ++it) {
            res.push_back( it->second );
        }
        return (res);
    }

    void AScene::debugTest(void)
    {
        std::cout << "GameObject List Size : " << _gameObjects.size() << std::endl;
    }

     void    AScene::mutexLock(bool lock)
     {
        if (lock)
            updateMutex.lock();
        else
            updateMutex.unlock();
     }

    void    AScene::start(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->start();
            (it->second)->componentStart();
        }
    }

    void    AScene::fixedUpdate(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->fixedUpdate();
            (it->second)->componentFixedUpdate();
        }
    }

    void    AScene::update(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->update();
            (it->second)->componentUpdate();
        }
    }

    void    AScene::renderUpdate(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->renderUpdate();
            (it->second)->componentRenderUpdate();
        }
    }

    void    AScene::render(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->render();
            (it->second)->componentRender();
        }
    }

    void    AScene::physicUpdate(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->componentPhysicUpdate();
        }
    }

    void    AScene::save(std::string filePath) {
        nlohmann::json j = dynamic_cast<JsonSerializable *>(this);
        std::string content = j.dump(4);
        BeerEngine::IO::FileUtils::WriteFile(filePath, content);
        // std::cout << content << std::endl;
    }

    void    AScene::load(std::string filePath) {
        std::string content = BeerEngine::IO::FileUtils::LoadFile(filePath);
        std::cout << "deserializing " << filePath << "\n";
        auto j = nlohmann::json::parse(content);
        this->deserialize(j);
    }

    nlohmann::json	AScene::serialize()
	{
		return nlohmann::json {
            {"gameObjects", JsonSerializable::toSerializables<BeerEngine::GameObject>(this->getGameObjects())},
        };
	}

    void AScene::deserialize(const nlohmann::json & j)
    {
        std::cout << "deserializing scene" << "\n";
        auto gameObjects = j.at("gameObjects");
        for (nlohmann::json::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {
            auto goJson = it.value();
            auto go = GameObject::Deserialize(goJson);
            this->_gameObjects.insert(std::pair<int, GameObject *>(go->getID(), go));
            go->start();
        }
    }
}