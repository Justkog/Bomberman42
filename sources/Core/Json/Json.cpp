#include "Core/Json/Json.hpp"

namespace glm
{
    void to_json(nlohmann::json& j, glm::vec2 & s) {
        std::cout << "glm to here!" << "\n";
        j = nlohmann::json {
            {"x", s.x},
            {"y", s.y}
        };
    }
}

namespace BeerEngine
{
    namespace Component
        {
        void to_json(nlohmann::json& j, Component * comp) {
            j = comp->serialize();
        }

        void from_json(const nlohmann::json& j, Component * comp) {
            // s.soundVolume = j.at("soundVolume").get<float>();
            // s.stringSetting = j.at("stringSetting").get<std::string>();
            // s.intSetting = j.at("intSetting").get<int>();
            // s.listSettings = j.at("listSettings").get<std::vector<std::string>>();
        }
    }

    void to_json(nlohmann::json& j, GameObject * s) {
        j = nlohmann::json {
            {"name", s->name},
            {"components", s->GetComponents()}
        };
        std::cout << "GO done!" << "\n";
        
    }

    void from_json(const nlohmann::json& j, GameObject * s) {
        // s.soundVolume = j.at("soundVolume").get<float>();
        // s.stringSetting = j.at("stringSetting").get<std::string>();
        // s.intSetting = j.at("intSetting").get<int>();
        // s.listSettings = j.at("listSettings").get<std::vector<std::string>>();
    }

    void to_json(nlohmann::json& j, BeerEngine::AScene& s) {
        glm::vec2 vec;
        vec.x = 10;
        std::cout << "serializeing!" << "\n";
        j = nlohmann::json {
            {"gameObjects", s.getGameObjects()},
            {"vec", vec}
        };
        std::cout << "done!" << "\n";
        
    }

    void from_json(const nlohmann::json& j, BeerEngine::AScene& s) {
        // s.soundVolume = j.at("soundVolume").get<float>();
        // s.stringSetting = j.at("stringSetting").get<std::string>();
        // s.intSetting = j.at("intSetting").get<int>();
        // s.listSettings = j.at("listSettings").get<std::vector<std::string>>();
    }
}