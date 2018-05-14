#ifndef BE_CORE_COMPONENT_IENABLE_HPP
#define BE_CORE_COMPONENT_IENABLE_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class IEnable
		{
		public:
			virtual void    enable(void) = 0;
		};
	}
}

#endif