#ifndef BE_CORE_COMPONENT_ICOLLIDER_ENTER_HPP
#define BE_CORE_COMPONENT_ICOLLIDER_ENTER_HPP 1
/*!
 * \file IColliderEnter.hpp
 * \brief Interface de d'entré en collision
 * \author qhonore
 */
namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ACollider;
		/*! \class IColliderEnter
		* \brief Interface quand une collision est appeler en sont depart
		*/
		class IColliderEnter
		{
		public:
			virtual void    onColliderEnter(ACollider *other) = 0;
		};
	}
}

#endif