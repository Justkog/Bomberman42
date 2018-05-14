#ifndef BE_CORE_COMPONENT_IONDESTROY_HPP
#define BE_CORE_COMPONENT_IONDESTROY_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class IOnDestroy
		{
		public:
			virtual void    onDestroy(void) = 0;
		};
	}
}

#endif