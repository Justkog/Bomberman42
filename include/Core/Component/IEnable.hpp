#ifndef BE_CORE_COMPONENT_IENABLE_HPP
#define BE_CORE_COMPONENT_IENABLE_HPP 1
/*!
 * \file IEnable.hpp
 * \brief Interface de d'activation du component.
 * \author jblondea
 */
namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		/*! \class IEnable
		* \brief Interface de d'activation du component.
		*/
		class IEnable
		{
		public:
			virtual void    enable(void) = 0;
		};
	}
}

#endif