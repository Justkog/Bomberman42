#ifndef BE_CORE_COMPONENT_ICOLLIDER_ENTER_HPP
#define BE_CORE_COMPONENT_ICOLLIDER_ENTER_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ACollider;

		class IColliderEnter
		{
		public:
			virtual void    onColliderEnter(ACollider *other) = 0;
		};
	}
}

#endif