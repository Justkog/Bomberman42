#ifndef BE_CORE_COMPONENT_ITRIGGER_ENTER_HPP
#define BE_CORE_COMPONENT_ITRIGGER_ENTER_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ACollider;

		class ITriggerEnter
		{
		public:
			virtual void    onTriggerEnter(ACollider *other) = 0;
		};
	}
}

#endif