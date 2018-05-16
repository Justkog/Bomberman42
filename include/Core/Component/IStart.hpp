#ifndef BE_CORE_COMPONENT_ISTART_HPP
#define BE_CORE_COMPONENT_ISTART_HPP 1
/*!
 * \file IStart.hpp
 * \brief Interface pour indiquer qu'on peu initialiser le component
 * \author mgallo
 */
/*! \namespace BeerEngine
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
	class GameObject;
	/*! \namespace Component
	* espace de nommage regroupant les fonctionnalité des Component du moteur
	*/
	namespace Component
	{
		/*! \class IStart
		* \brief Interface avec la fonctionnalité d'initialiser le component.
		*/
		class IStart
		{
		public:
			virtual void    start(void) = 0;
		};
	}
}

#endif