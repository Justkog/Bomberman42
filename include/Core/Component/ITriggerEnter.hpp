#ifndef BE_CORE_COMPONENT_ITRIGGER_ENTER_HPP
#define BE_CORE_COMPONENT_ITRIGGER_ENTER_HPP 1
/*!
 * \file ITriggerEnter.hpp
 * \brief Interface de d'entré dans un declancheur
 * \author qhonore
 */
namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ACollider;
		/*! \class ITriggerEnter
		* \brief Interface quand un déclancheur est appeler en sont depart
		*/
		class ITriggerEnter
		{
		public:
			virtual void    onTriggerEnter(ACollider *other) = 0;
		};
	}
}

#endif