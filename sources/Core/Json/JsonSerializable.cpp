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
}