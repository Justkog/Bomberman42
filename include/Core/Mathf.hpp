#ifndef BE_CORE_MATHF_HPP
#define BE_CORE_MATHF_HPP 1
/*!
 * \file Mathf.hpp
 * \brief fonction mathematique supplementaire
 * \author mgallo
 */
#include "Core.hpp"
/*! \namespace BeerEngine
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
	/*! \class Mathf
	* \brief classe permettent d'acceder a des fonctions mathematique personnaliser pour le moteur
	*/
	class Mathf
	{
	public:
		/*!
		*  \brief recuperer un valeur aleatoire
		*  Methode qui permet de recuperer une valeur aleatoire dans un ecart donner
		*  \param min : valeur minimal de l'ecart
		*  \param max : valeur maximal de l'ecart
		*  \return valeur aleatoire
		*/
		static float Range(float min, float max);
		static glm::mat4		assimp_to_glm(aiMatrix4x4 mat);
		static aiMatrix4x4		glm_to_assimp(glm::mat4 mat);
	};
}

#endif