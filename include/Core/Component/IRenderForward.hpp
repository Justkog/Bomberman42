#ifndef BE_CORE_COMPONENT_IRENDERFORWARD_HPP
#define BE_CORE_COMPONENT_IRENDERFORWARD_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Graphics
	{
		class ALight;
	} 

	namespace Component
	{
		class IRenderForward
		{
		public:
			virtual void    renderUpdate(void) = 0;
			virtual void    render(BeerEngine::Graphics::ALight &light) = 0;
		};
	}
}

#endif