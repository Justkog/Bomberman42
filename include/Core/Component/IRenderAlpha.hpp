#ifndef BE_CORE_COMPONENT_IRENDERALPHA_HPP
#define BE_CORE_COMPONENT_IRENDERALPHA_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class IRenderAlpha
		{
		public:
			virtual void    renderAlphaUpdate(void) = 0;
			virtual void    renderAlpha(void) = 0;
		};
	}
}

#endif