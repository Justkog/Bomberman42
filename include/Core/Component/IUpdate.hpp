#ifndef BE_CORE_COMPONENT_IUPDATE_HPP
#define BE_CORE_COMPONENT_IUPDATE_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class IUpdate
		{
		public:
			virtual void    fixedUpdate(void) = 0;
       		virtual void    update(void) = 0;
		};
	}
}

#endif