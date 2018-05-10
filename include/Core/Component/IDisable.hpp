#ifndef BE_CORE_COMPONENT_IDISABLE_HPP
#define BE_CORE_COMPONENT_IDISABLE_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class IDisable
		{
		public:
			virtual void    disable(void) = 0;
		};
	}
}

#endif