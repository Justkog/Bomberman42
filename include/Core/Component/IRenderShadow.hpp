#ifndef BE_CORE_COMPONENT_IRENDERSHADOW_HPP
#define BE_CORE_COMPONENT_IRENDERSHADOW_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class IRenderShadow
		{
		public:
			virtual void    renderShadowUpdate(void) = 0;
			virtual void    renderShadow(void) = 0;
			virtual bool	castShadows(void) = 0;
			virtual bool	receiveShadows(void) = 0;
		};
	}
}

#endif