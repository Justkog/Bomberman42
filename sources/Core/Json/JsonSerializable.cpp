#include "Core/Json/JsonSerializable.hpp"

namespace BeerEngine
{
    JsonSerializable &JsonSerializable::toSerializable(JsonSerializable & item)
    {
        return item;
    }

    JsonSerializable *JsonSerializable::toSerializable(JsonSerializable * item)
    {
        return item;
    }

    void JsonDeserializable::deserialize(const nlohmann::json & j)
    {

    }

    void JsonDeserializable::Deserialize(const nlohmann::json & j)
    {
        
    }

}