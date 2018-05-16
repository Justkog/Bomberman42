#ifndef BE_CORE_COMPONENT_IENABLE_HPP
#define BE_CORE_COMPONENT_IENABLE_HPP 1
/*!
 * \file IEnable.hpp
 * \brief 
 * \author jblondea
 */
namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		/*! \class IEnable
		* \brief 
		*/
		class IEnable
		{
		public:
			virtual void    enable(void) = 0;
		};
	}
}

#endif