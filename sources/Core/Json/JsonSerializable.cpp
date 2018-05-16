#include "Core/Json/JsonSerializable.hpp"

namespace BeerEngine
{
	int JsonSerializable::idCounter = 0;

	JsonSerializable::JsonSerializable()
	{
		_serializationID = idCounter++;
		// std::cout << "json serializable created with id " << _serializationID << std::endl;
	}

    JsonSerializable &JsonSerializable::toSerializable(JsonSerializable & item)
    {
        return item;
    }

    JsonSerializable *JsonSerializable::toSerializable(JsonSerializable * item)
    {
        return item;
    }

	nlohmann::json	JsonSerializable::serialize()
	{
		return nlohmann::json {
			{"serializationID", _serializationID},
		};
	}

	void JsonSerializable::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
    {
		_serializationID = j.at("serializationID");
		loader.serializables[_serializationID] = this;
    }

	void JsonLoader::executeCallBacks()
	{
		// std::cout << "executing jsonLoader callbacks" << std::endl;
		while (!serializationCallBacks.empty())
		{
			serializationCallBacks.top()();
			serializationCallBacks.pop();
		}
	}

	JsonSerializable *JsonLoader::getSerializableByID(int id)
	{
		auto it = serializables.find(id);
  		if (it != serializables.end())
    		return it->second;
		return NULL;
	}
}