#include "Core/Json/Json.hpp"
#include "Core/Component/Component.hpp"
#include "Core/GameObject.hpp"
#include "Core/Transform.hpp"
#include "Core/AScene.hpp"
#include "Core/Json/JsonSerializable.hpp"

namespace glm
{
    void to_json(nlohmann::json& j, glm::vec2 & item) {
        j = nlohmann::json {item.x, item.y};
    }

    void to_json(nlohmann::json& j, glm::vec3 & item) {
        j = nlohmann::json {item.x, item.y};
    }

    void to_json(nlohmann::json& j, glm::quat & item) {
        j = nlohmann::json {item.w, item.x, item.y, item.z};
    }
}

namespace BeerEngine
{
    void to_json(nlohmann::json& j, JsonSerializable & item) {
        j = item.serialize();
    }

    void from_json(const nlohmann::json& j, JsonSerializable & item) {
        
    }

    void to_json(nlohmann::json& j, JsonSerializable * item) {
        if (item)
            j = item->serialize();
        else
            j = nlohmann::json {};
    }

    void from_json(const nlohmann::json& j, JsonSerializable * item) {
        
    }
}