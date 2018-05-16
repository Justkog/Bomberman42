#ifndef BE_CORE_COMPONENT_ICOLLIDER_EXIT_HPP
#define BE_CORE_COMPONENT_ICOLLIDER_EXIT_HPP 1
/*!
 * \file IColliderExit.hpp
 * \brief Interface de de sortie de collision
 * \author qhonore
 */
namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ACollider;
		/*! \class IColliderExit
		* \brief Interface quand une collision est appeler a ca sortie
		*/
		class IColliderExit
		{
		public:
			virtual void    onColliderExit(ACollider *other) = 0;
		};
	}
}

#endif