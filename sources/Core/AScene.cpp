#include "Core/AScene.hpp"
// #include <nlohmann/json.hpp>
// #include <glm/glm.hpp>
#include "Core/Json/Json.hpp"

// namespace glm
// {
//     void to_json(nlohmann::json& j, glm::vec2 & s) {
//         std::cout << "glm to here!" << "\n";
//         j = nlohmann::json {
//             {"x", s.x},
//             {"y", s.y}
//         };
//     }
// }

// void to_json(nlohmann::json& j, glm::vec2 & s) {
//     std::cout << "glm to here!" << "\n";
//     j = nlohmann::json {
//         {"x", s.x},
//         {"y", s.y}
//     };
// }

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
        nlohmann::json j = *this;
        std::string content = j.dump(4);
        BeerEngine::IO::FileUtils::WriteFile(filePath, content);
        std::cout << content << std::endl;
    }

    // void to_json(nlohmann::json& j, glm::vec2 & s) {
    //     std::cout << "glm to here!" << "\n";
    //     j = nlohmann::json {
    //         {"x", s.x},
    //         {"y", s.y}
    //     };
    // }

    // namespace Component
	// {
    //     void to_json(nlohmann::json& j, Component * comp) {
    //         j = comp->serialize();
    //     }

    //     void from_json(const nlohmann::json& j, Component * comp) {
    //         // s.soundVolume = j.at("soundVolume").get<float>();
    //         // s.stringSetting = j.at("stringSetting").get<std::string>();
    //         // s.intSetting = j.at("intSetting").get<int>();
    //         // s.listSettings = j.at("listSettings").get<std::vector<std::string>>();
    //     }
    // }

    // void to_json(nlohmann::json& j, GameObject * s) {
    //     j = nlohmann::json {
    //         {"name", s->name},
    //         {"components", s->GetComponents()}
    //     };
    //     std::cout << "GO done!" << "\n";
        
    // }

    // void from_json(const nlohmann::json& j, GameObject * s) {
    //     // s.soundVolume = j.at("soundVolume").get<float>();
    //     // s.stringSetting = j.at("stringSetting").get<std::string>();
    //     // s.intSetting = j.at("intSetting").get<int>();
    //     // s.listSettings = j.at("listSettings").get<std::vector<std::string>>();
    // }

    // void to_json(nlohmann::json& j, AScene& s) {
    //     glm::vec2 vec;
    //     vec.x = 10;
    //     std::cout << "serializeing!" << "\n";
    //     j = nlohmann::json {
    //         {"gameObjects", s.getGameObjects()},
    //         {"vec", vec}
    //     };
    //     std::cout << "done!" << "\n";
        
    // }

    // void from_json(const nlohmann::json& j, AScene& s) {
    //     // s.soundVolume = j.at("soundVolume").get<float>();
    //     // s.stringSetting = j.at("stringSetting").get<std::string>();
    //     // s.intSetting = j.at("intSetting").get<int>();
    //     // s.listSettings = j.at("listSettings").get<std::vector<std::string>>();
    // }
}