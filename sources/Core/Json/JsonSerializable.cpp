#include "Core/Json/JsonSerializable.hpp"

namespace BeerEngine
{
	int JsonSerializable::idCounter = 0;
	std::map<int, JsonSerializable *> JsonSerializable::serializables;
	std::stack<std::function<void (void)>> JsonSerializable::serializationCallBacks;

	JsonSerializable::JsonSerializable()
	{
		_serializationID = idCounter++;
		std::cout << "json serializable created with id " << _serializationID << std::endl;
		serializables[_serializationID] = this;
	}

	// JsonSerializable::JsonSerializable(int id) :
	// 	_serializationID(id)
	// {
	// 	std::cout << "json serializable created with id " << _serializationID << std::endl;
	// 	serializables[_serializationID] = this;
	// }

	JsonSerializable *JsonSerializable::GetSerializableByID(int id)
	{
		auto it = serializables.find(id);
  		if (it != serializables.end())
    		return it->second;
		return NULL;
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

	void JsonSerializable::deserialize(const nlohmann::json & j)
    {
		_serializationID = j.at("serializationID");
		serializables[_serializationID] = this;
    }

	void JsonSerializable::ExecuteCallBacks()
	{
		while (!serializationCallBacks.empty())
		{
			std::cout << "executing callback on " << std::endl;
			serializationCallBacks.top()();
			serializationCallBacks.pop();
		}
	}

	// void JsonSerializable::deserializeLinks(const nlohmann::json & j)
	// {

	// }
    
	
	
	
	
	
	
	
	
	
	void JsonDeserializable::deserialize(const nlohmann::json & j)
    {

    }


    void JsonDeserializable::Deserialize(const nlohmann::json & j)
    {
        
    }

}