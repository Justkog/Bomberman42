#ifndef BE_CORE_TIMER_HPP
#define BE_CORE_TIMER_HPP 1

/*!
 * \file Time.hpp
 * \brief gestion du temps
 * \author mgallo
 */

#include "Core.hpp"
/*! \namespace BeerEngine
 * 
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
    /*! \class Time
	* \brief classe representant le temps
	*/
    class Time
    {
    private:
        static double   _LastTime; /*!< Dernier temps sauvegarder*/
        static double   _DeltaTime; /*!< Delta time enregistrer au dernier tour de boucle*/
    
    public:
        /*!
		*  \brief mettre a jour le temps
		*  Methode qui permet de mettre a jour le delta time
		*/
        static void     Update(void);
        /*!
		*  \brief recuperer les delta time
		*  Methode qui permet de recuperer le delta time (ecart entre deux cycle de l'update)
		*  \return delta time
		*/
        static double   GetDeltaTime(void);
    };
}

#endif