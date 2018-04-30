#ifndef BE_CORE_JSON_SERIALIZABLE_HPP
#define BE_CORE_JSON_SERIALIZABLE_HPP 1

#include "Core/Core.hpp"

namespace BeerEngine
{
    class JsonSerializable
    {
    public:
        virtual nlohmann::json	serialize() = 0;
        static JsonSerializable &toSerializable(JsonSerializable & item);
        static JsonSerializable *toSerializable(JsonSerializable * item);

        template<typename T>
        std::vector<JsonSerializable *> toSerializables(std::vector<T *> items)
        {
            std::vector<JsonSerializable *> serializables;
            for (auto item: items)
            {
                serializables.push_back(item);
            }
            return serializables;
        }
    };

    class JsonDeserializable
    {
    public:
        virtual void deserialize(const nlohmann::json & j);
        static void Deserialize(const nlohmann::json & j);
    };
}

#endif