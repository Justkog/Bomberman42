#ifndef BE_CORE_JSON_HPP
#define BE_CORE_JSON_HPP 1

#include "Core/Core.hpp"
#include "Core/Json/JsonSerializable.hpp"

namespace glm
{
    void to_json(nlohmann::json& j, glm::vec2 & item);
    void from_json(const nlohmann::json& j, glm::vec2 & item);
    
    void to_json(nlohmann::json& j, glm::vec3 & item);
    void from_json(const nlohmann::json& j, glm::vec3 & item);

    void to_json(nlohmann::json& j, glm::vec4 & item);
    void from_json(const nlohmann::json& j, glm::vec4 & item);

    void to_json(nlohmann::json& j, glm::quat & item);
    void from_json(const nlohmann::json& j, glm::quat & item);

    void to_json(nlohmann::json& j, glm::mat4 & item);
    void from_json(const nlohmann::json& j, glm::mat4 & item);
}

namespace BeerEngine
{
    void to_json(nlohmann::json& j, JsonSerializable & item);
    void from_json(const nlohmann::json& j, JsonDeserializable & item);
    void to_json(nlohmann::json& j, JsonSerializable * item);
    void from_json(const nlohmann::json& j, JsonDeserializable * item);
}
#endif