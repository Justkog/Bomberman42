#ifndef BE_CORE_JSON_HPP
#define BE_CORE_JSON_HPP 1

#include <nlohmann/json.hpp>
#include "Core/Core.hpp"
#include "Core/AScene.hpp"
#include "Core/Component/Component.hpp"
#include "Core/GameObject.hpp"
#include <glm/glm.hpp>

namespace glm
{
    void to_json(nlohmann::json& j, glm::vec2 & s);
}

namespace BeerEngine
{
    class AScene;
    namespace Component
        {
        void to_json(nlohmann::json& j, Component * comp);

        void from_json(const nlohmann::json& j, Component * comp);
    }

    void to_json(nlohmann::json& j, GameObject * s);

    void from_json(const nlohmann::json& j, GameObject * s);

    void to_json(nlohmann::json& j, BeerEngine::AScene& s);

    void from_json(const nlohmann::json& j, BeerEngine::AScene& s);
}
#endif