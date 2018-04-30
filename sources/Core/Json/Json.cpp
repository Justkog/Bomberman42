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

    void from_json(const nlohmann::json& j, glm::vec2 & item)
    {
        item.x = j.at(0);
        item.y = j.at(1);
    }

    void to_json(nlohmann::json& j, glm::vec3 & item) {
        j = nlohmann::json {item.x, item.y, item.z};
    }

    void from_json(const nlohmann::json& j, glm::vec3 & item)
    {
        item.x = j.at(0);
        item.y = j.at(1);
        item.z = j.at(2);
    }

    void to_json(nlohmann::json& j, glm::vec4 & item) {
        j = nlohmann::json {item.w, item.x, item.y, item.z};
    }

    void from_json(const nlohmann::json& j, glm::vec4 & item)
    {
        item.w = j.at(0);
        item.x = j.at(1);
        item.y = j.at(2);
        item.z = j.at(3);
    }

    void to_json(nlohmann::json& j, glm::quat & item) {
        j = nlohmann::json {item.w, item.x, item.y, item.z};
    }

    void from_json(const nlohmann::json& j, glm::quat & item)
    {
        item.w = j.at(0);
        item.x = j.at(1);
        item.y = j.at(2);
        item.z = j.at(3);
    }

    void to_json(nlohmann::json& j, glm::mat4 & item) {
        j = nlohmann::json {
            {item[0][0], item[0][1], item[0][2], item[0][3]},
            {item[1][0], item[1][1], item[1][2], item[1][3]},
            {item[2][0], item[2][1], item[2][2], item[2][3]},
            {item[3][0], item[3][1], item[3][2], item[3][3]},
        };
    }

    void from_json(const nlohmann::json& j, glm::mat4 & item)
    {
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                item[row][col] = j.at(col + row * 4);
            }
        }
    }
}

namespace BeerEngine
{
    void to_json(nlohmann::json& j, JsonSerializable & item) {
        j = item.serialize();
    }

    void from_json(const nlohmann::json& j, JsonDeserializable & item) {
        item.deserialize(j);
    }

    void to_json(nlohmann::json& j, JsonSerializable * item) {
        if (item)
            j = item->serialize();
        else
            j = nlohmann::json {};
    }

    void from_json(const nlohmann::json& j, JsonDeserializable * item) {
        item->deserialize(j);
    }

    void from_json(const nlohmann::json& j, GameObject & item) {
        item.deserialize(j);
    }

    void from_json(const nlohmann::json& j, GameObject * item) {
        item->deserialize(j);
    }
}