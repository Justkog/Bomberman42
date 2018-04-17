#ifndef BE_CORE_COMPONENT_IRENDER_HPP
#define BE_CORE_COMPONENT_IRENDER_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class IRender
		{
		public:
			virtual void    renderUpdate(void) = 0;
			virtual void    render(void) = 0;
		};
	}
}

#endif