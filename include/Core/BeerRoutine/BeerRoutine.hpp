#ifndef BE_CORE_BEER_ROUTINE_HPP
#define BE_CORE_BEER_ROUTINE_HPP 1
/*!
 * \file BeerRoutine.hpp
 * \brief Routine
 * \author jblondea
 */
#include "Core/Core.hpp"

namespace BeerEngine
{
	namespace BeerRoutine
	{
		/*! \class BeerRoutine
		* \brief Routine utilisable par le gestionnaire de routines.
		*/
		class BeerRoutine
		{
		private:
			std::vector<std::function<bool (void)>> _actions;
			float	_timer;
			bool	_loop;

			BeerRoutine(const BeerRoutine &val);
			BeerRoutine &operator=(const BeerRoutine &val);
		public:
			BeerRoutine();
			virtual ~BeerRoutine();

			/*!
			*  \brief Ajout d'action
			*  Ajout d'une action à la liste des actions (l'action est répetée tant que le retour est false).
			*/
			BeerRoutine &addAction(std::function<bool (void)> action);

			/*!
			*  \brief Ajout d'un timer
			*  Ajout d'un timer permettant de n'exécuter aucune action pendant le temps indiqué.
			*/
			BeerRoutine &addTimer(float seconds);
			
			/*!
			*  \brief Exécution en boucle
			*  Requête d'exécution en boucle de la routine (jusqu'à son arrêt par le gestionnaire).
			*/
			BeerRoutine &loop();

			/*!
			*  \brief Instanciation d'une routine sans action
			*/
			static BeerRoutine &CreateRoutine();

			void	update();
			bool	hasActionsLeft();
		};
	}
}

#endif