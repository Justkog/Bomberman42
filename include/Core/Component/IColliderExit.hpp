#ifndef BE_CORE_COMPONENT_ICOLLIDER_EXIT_HPP
#define BE_CORE_COMPONENT_ICOLLIDER_EXIT_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ACollider;

		class IColliderExit
		{
		public:
			virtual void    onColliderExit(ACollider *other) = 0;
		};
	}
}

#endif