#include "Game/Components/Breakable.hpp"

namespace Game
{
	namespace Component
	{

		Breakable::Breakable(BeerEngine::GameObject *gameObject):
		Component(gameObject),
		_transform(gameObject->transform),
		_posX(_transform.position.x),
		_posY(_transform.position.y)
		{ }

		void	destroyed()
		{
			// _map.mapUpdate(_posX, _posY);
		}

		nlohmann::json	Breakable::serialize()
		{
			return nlohmann::json {
				{"componentClass", type},
			};
		}

		void Breakable::deserialize(const nlohmann::json & j)
		{
			// std::cout << this->_sourceFile << "\n";
			// this->_sourceFile = j.at("sourceFile");
			// if (this->_sourceFile != "")
			// 	this->setMesh(this->_sourceFile);
		}

		REGISTER_COMPONENT_CPP(Breakable)
	}
}
