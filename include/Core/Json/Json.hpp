#ifndef BE_CORE_JSON_HPP
#define BE_CORE_JSON_HPP 1

#include "Core/Core.hpp"
#include "Core/Json/JsonSerializable.hpp"

namespace glm
{
    void to_json(nlohmann::json& j, glm::vec2 & item);
    void to_json(nlohmann::json& j, glm::vec3 & item);
    void to_json(nlohmann::json& j, glm::quat & item);
}

namespace BeerEngine
{
    void to_json(nlohmann::json& j, Transform & item);
    void from_json(const nlohmann::json& j, Transform & item);
    void to_json(nlohmann::json& j, Transform * item);
    void from_json(const nlohmann::json& j, Transform * item);

    namespace Component
    {
        void to_json(nlohmann::json& j, Component * comp);
        void from_json(const nlohmann::json& j, Component * comp);
    }

    void to_json(nlohmann::json& j, GameObject * s);
    void from_json(const nlohmann::json& j, GameObject * s);

    // void to_json(nlohmann::json& j, BeerEngine::AScene& s);
    // void from_json(const nlohmann::json& j, BeerEngine::AScene& s);

    void to_json(nlohmann::json& j, JsonSerializable & item);
    void from_json(const nlohmann::json& j, JsonSerializable & item);
    void to_json(nlohmann::json& j, JsonSerializable * item);
    void from_json(const nlohmann::json& j, JsonSerializable * item);
}
#endif