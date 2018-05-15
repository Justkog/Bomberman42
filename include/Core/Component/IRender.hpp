#ifndef BE_CORE_COMPONENT_IRENDER_HPP
#define BE_CORE_COMPONENT_IRENDER_HPP 1
/*!
 * \file IRender.hpp
 * \brief Interface pour indiquer qu'il y a un rendu standard
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
		/*! \class IRender
		* \brief Interface avec les fonctionnalités pour effectuer un rendu standard
		*/
		class IRender
		{
		public:
			virtual void    renderUpdate(void) = 0;
			virtual void    render(void) = 0;
		};
	}
}

#endif