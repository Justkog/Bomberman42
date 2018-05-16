#ifndef BE_CORE_COMPONENT_ICOLLIDER_STAY_HPP
#define BE_CORE_COMPONENT_ICOLLIDER_STAY_HPP 1
/*!
 * \file IColliderStay.hpp
 * \brief Interface de collision constante
 * \author qhonore
 */
namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ACollider;
		/*! \class IColliderStay
		* \brief Interface quand une collision est appeler constament, tant que les deux objets sont en collision
		*/
		class IColliderStay
		{
		public:
			virtual void    onColliderStay(ACollider *other) = 0;
		};
	}
}

#endif