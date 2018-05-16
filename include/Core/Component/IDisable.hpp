#ifndef BE_CORE_COMPONENT_IDISABLE_HPP
#define BE_CORE_COMPONENT_IDISABLE_HPP 1
/*!
 * \file IDisable.hpp
 * \brief Interface de désactivation du component.
 * \author jblondea
 */
namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		/*! \class IDisable
		* \brief Interface de désactivation du component.
		*/
		class IDisable
		{
		public:
			virtual void    disable(void) = 0;
		};
	}
}

#endif