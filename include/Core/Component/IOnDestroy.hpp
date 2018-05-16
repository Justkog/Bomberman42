#ifndef BE_CORE_COMPONENT_IONDESTROY_HPP
#define BE_CORE_COMPONENT_IONDESTROY_HPP 1
/*!
 * \file IOnDestroy.hpp
 * \brief Interface de pre-destruction
 * \author qhonore
 */
namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		/*! \class IOnDestroy
		* \brief Interface permettant d'effectuer des actions avant la destruction.
		*/
		class IOnDestroy
		{
		public:
			virtual void    onDestroy(void) = 0;
		};
	}
}

#endif