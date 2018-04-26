#ifndef BE_CORE_COMPONENT_ITRIGGER_STAY_HPP
#define BE_CORE_COMPONENT_ITRIGGER_STAY_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ACollider;

		class ITriggerStay
		{
		public:
			virtual void    onTriggerStay(ACollider *other) = 0;
		};
	}
}

#endif