#ifndef BE_CORE_AROUTINE_RUNNER_HPP
#define BE_CORE_AROUTINE_RUNNER_HPP 1
/*!
 * \file ARoutineRunner.hpp
 * \brief Classe implémentant un systeme de routine
 * \author jblondea
 */
#include "Core/Core.hpp"

namespace BeerEngine
{
	namespace BeerRoutine
	{
		/*! \class ARoutineRunner
		* \brief Gestionnaire de routines permettant de demarrer une nouvelle routine ou de stopper une routine en cours
		*/
		class ARoutineRunner
		{
		private:
			std::vector<BeerEngine::BeerRoutine::BeerRoutine *> _currentRoutines;

		public:
			virtual void update();

			void startRoutine(BeerEngine::BeerRoutine::BeerRoutine &routine);
			void stopRoutine(BeerEngine::BeerRoutine::BeerRoutine *routine);
			std::vector<BeerEngine::BeerRoutine::BeerRoutine *> getRunningRoutines();

		};
	}
}

#endif