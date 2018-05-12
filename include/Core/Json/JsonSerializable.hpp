#ifndef BE_CORE_JSON_SERIALIZABLE_HPP
#define BE_CORE_JSON_SERIALIZABLE_HPP 1

#include "Core/Core.hpp"

namespace BeerEngine
{
    class JsonSerializable
    {
	private:
		static int idCounter;
		static std::map<int, JsonSerializable *> serializables;

    public:
		int			_serializationID;
		static std::stack<std::function<void (void)>> serializationCallBacks;

		JsonSerializable();
		JsonSerializable(int id);

        virtual nlohmann::json	serialize();
		virtual void deserialize(const nlohmann::json & j);
		// virtual void deserializeLinks(const nlohmann::json & j);
        static void Deserialize(const nlohmann::json & j);
		static JsonSerializable *GetSerializableByID(int id);
		static void ExecuteCallBacks();

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