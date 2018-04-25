#ifndef BE_CORE_COMPONENT_ITRIGGER_EXIT_HPP
#define BE_CORE_COMPONENT_ITRIGGER_EXIT_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ITriggerExit
		{
		public:
			virtual void    onTriggerExit(void) = 0;
		};
	}
}

#endif