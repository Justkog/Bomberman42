#ifndef BE_CORE_COMPONENT_IUPDATE_HPP
#define BE_CORE_COMPONENT_IUPDATE_HPP 1
/*!
 * \file IUpdate.hpp
 * \brief Interface pour indiquer qu'on peu mettre a jour le component
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
		/*! \class IUpdate
		* \brief Interface avec les fonctionnalités pour effectuer les updates
		*/
		class IUpdate
		{
		public:
			virtual void    fixedUpdate(void) = 0;
       		virtual void    update(void) = 0;
		};
	}
}

#endif