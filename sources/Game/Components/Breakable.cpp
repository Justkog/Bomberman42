#include "Game/Components/Breakable.hpp"

namespace Game
{
	namespace Component
	{

		Breakable::Breakable(BeerEngine::GameObject *gameObject):
		Component(gameObject),
		_transform(gameObject->transform)
		{ }

		Breakable::~Breakable(void)
		{
			destroyed();
		}

		void	Breakable::destroyed()
		{
			onDestruction.emit(_transform.position, 0);
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
