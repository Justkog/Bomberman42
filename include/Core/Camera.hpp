#ifndef BE_CORE_CAMERA_HPP
#define BE_CORE_CAMERA_HPP 1
/*!
 * \file Camera.hpp
 * \brief Camera du projet
 * \author mgallo
 */
#include "Core.hpp"
#include "Transform.hpp"
/*! \namespace BeerEngine
 * 
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
	/*! \class Camera
	* \brief classe la camera du projet, ainsi permettant l'acces de la view matrice dans tout le projet
	*/
	class Camera {
	public:
		static Camera	*main; /*!< Instance de la camera principal*/

		Transform	transform; /*!< Transforme de la camera, position et rotation*/
	};
}

#endif