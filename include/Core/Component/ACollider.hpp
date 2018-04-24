#ifndef BE_CORE_COMPONENT_ACOLLIDER_HPP
#define BE_CORE_COMPONENT_ACOLLIDER_HPP 1

#include "../BeerEngine.hpp"
#include "Component.hpp"
#include "IUpdate.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class ACollider : public Component, public IUpdate
		{
		protected:
			Maths::Vector2f	_offset;
			Maths::Vector2f	_size;
			Transform	&_transform;

		public:
			ACollider(GameObject *gameObject);
			Maths::Vector2f getOffset(void);
			ACollider &setOffset(Maths::Vector2f &offset);
			Maths::Vector2f getSize(void);
			ACollider &setSize(Maths::Vector2f &size);
			virtual void    fixedUpdate(void);
			virtual void    update(void);

		};
	}
}

#endif