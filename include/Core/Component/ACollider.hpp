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
			glm::vec2	_offset;
			glm::vec2	_size;
			Transform	&_transform;

		public:
			ACollider(GameObject *gameObject);
			glm::vec2 getOffset(void);
			ACollider &setOffset(glm::vec2 &offset);
			glm::vec2 getSize(void);
			ACollider &setSize(glm::vec2 &size);
			virtual void    fixedUpdate(void);
			virtual void    update(void);

		};
	}
}

#endif