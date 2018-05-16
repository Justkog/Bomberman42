#ifndef BE_CORE_COMPONENT_IRENDERALPHA_HPP
#define BE_CORE_COMPONENT_IRENDERALPHA_HPP 1
/*!
 * \file IRenderAlpha.hpp
 * \brief Interface pour indiquer qu'il y a un rendu avec de la transparence
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
		/*! \class IRenderAlpha
		* \brief Interface avec les fonctionnalités pour effectuer un rendu avec de la transparence
		*/
		class IRenderAlpha
		{
		public:
			virtual void    renderAlphaUpdate(void) = 0;
			virtual void    renderAlpha(void) = 0;
		};
	}
}

#endif