#ifndef BE_CORE_COMPONENT_ICOLLIDER_STAY_HPP
#define BE_CORE_COMPONENT_ICOLLIDER_STAY_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ACollider;

		class IColliderStay
		{
		public:
			virtual void    onColliderStay(ACollider *other) = 0;
		};
	}
}

#endif