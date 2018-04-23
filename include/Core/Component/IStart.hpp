#ifndef BE_CORE_COMPONENT_ISTART_HPP
#define BE_CORE_COMPONENT_ISTART_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class IStart
		{
		public:
			virtual void    start(void) = 0;
		};
	}
}

#endif