#ifndef BE_CORE_COMPONENT_ITRIGGER_STAY_HPP
#define BE_CORE_COMPONENT_ITRIGGER_STAY_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ITriggerStay
		{
		public:
			virtual void    onTriggerStay(void) = 0;
		};
	}
}

#endif