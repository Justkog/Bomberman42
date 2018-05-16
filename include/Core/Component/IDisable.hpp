#ifndef BE_CORE_COMPONENT_IDISABLE_HPP
#define BE_CORE_COMPONENT_IDISABLE_HPP 1
/*!
 * \file IDisable.hpp
 * \brief 
 * \author jblondea
 */
namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		/*! \class IDisable
		* \brief 
		*/
		class IDisable
		{
		public:
			virtual void    disable(void) = 0;
		};
	}
}

#endif