#ifndef BE_CORE_COMPONENT_ITRIGGER_EXIT_HPP
#define BE_CORE_COMPONENT_ITRIGGER_EXIT_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ACollider;

		class ITriggerExit
		{
		public:
			virtual void    onTriggerExit(ACollider *other) = 0;
		};
	}
}

#endif