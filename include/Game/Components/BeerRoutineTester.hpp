// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef BEERROUTINETESTER_HPP
# define BEERROUTINETESTER_HPP

/*!
 * \file BeerRoutineTester.hpp
 * \brief Exemple d'utilisation des routines
 * \author jblondea
 */

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/BeerRoutine/BeerRoutine.hpp"
#include "Core/BeerRoutine/ARoutineRunner.hpp"

namespace Game
{
	namespace Component
	{
		class BeerRoutineTester : public BeerEngine::Component::Component,
									public BeerEngine::Component::IUpdate,
									public BeerEngine::Component::IStart,
									public BeerEngine::BeerRoutine::ARoutineRunner
		{
		private:
			BeerRoutineTester();
			BeerRoutineTester(const BeerRoutineTester &val);
			BeerRoutineTester & operator=( BeerRoutineTester const & rhs );

		public:	
			BeerRoutineTester(BeerEngine::GameObject *gameObject);
			virtual ~BeerRoutineTester( void );

			friend std::ostream & operator<<(std::ostream & o, BeerRoutineTester const & i);

			virtual void start();
			virtual void update();
			virtual void fixedUpdate();

			void	testDisplay(std::string content);
			BeerEngine::BeerRoutine::BeerRoutine *createTestRoutine();
		};

	};

};

#endif
