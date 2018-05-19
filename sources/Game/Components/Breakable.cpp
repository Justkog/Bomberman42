#include "Game/Components/Breakable.hpp"

namespace Game
{
	namespace Component
	{

		Breakable::Breakable(BeerEngine::GameObject *gameObject):
		Component(gameObject),
		_transform(gameObject->transform)
		{ }

		Breakable::Breakable(void) :
            _transform(BeerEngine::Transform::basic)
		{}

		Breakable::Breakable(const Breakable &val) :
            _transform(BeerEngine::Transform::basic)
		{
			*this = val;
		}

		Breakable &Breakable::operator=(const Breakable &val)
		{
			(void) val;
			if (this != &val)
			{ }
			return (*this);
		}

		Breakable::~Breakable(void)
		{
			destroyed();
		}

		void	Breakable::destroyed()
		{
			onDestruction.emit(_transform.position, 0);
			onDestructionSelf.emit(this);
		}

		nlohmann::json	Breakable::serialize()
		{
			auto j = Component::serialize();
			j.merge_patch({
				{"componentClass", type},
			});
			return j;
		}

		void Breakable::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			Component::deserialize(j, loader);
		}

		REGISTER_COMPONENT_CPP(Breakable)
	}
}
