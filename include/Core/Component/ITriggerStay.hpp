#ifndef BE_CORE_COMPONENT_ITRIGGER_STAY_HPP
#define BE_CORE_COMPONENT_ITRIGGER_STAY_HPP 1
/*!
 * \file ITriggerStay.hpp
 * \brief Interface de déclancheur constante
 * \author qhonore
 */
namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ACollider;
		/*! \class ITriggerStay
		* \brief Interface quand un déclancheur est appeler constament
		*/
		class ITriggerStay
		{
		public:
			virtual void    onTriggerStay(ACollider *other) = 0;
		};
	}
}

#endif