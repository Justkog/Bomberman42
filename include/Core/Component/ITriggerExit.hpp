#ifndef BE_CORE_COMPONENT_ITRIGGER_EXIT_HPP
#define BE_CORE_COMPONENT_ITRIGGER_EXIT_HPP 1
/*!
 * \file ITriggerExit.hpp
 * \brief Interface de de sortie d'un déclancheur
 * \author qhonore
 */
namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class ACollider;
		/*! \class ITriggerExit
		* \brief Interface quand un déclancheur est appeler a ca sortie
		*/
		class ITriggerExit
		{
		public:
			virtual void    onTriggerExit(ACollider *other) = 0;
		};
	}
}

#endif