#ifndef BE_CORE_COMPONENT_ITRIGGER_ENTER_HPP
#define BE_CORE_COMPONENT_ITRIGGER_ENTER_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ITriggerEnter
		{
		public:
			virtual void    onTriggerEnter(void) = 0;
		};
	}
}

#endif