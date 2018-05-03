// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef BEERROUTINETESTER_HPP
# define BEERROUTINETESTER_HPP

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"

namespace Game
{
	namespace Component
	{
		class BeerRoutineTester : public BeerEngine::Component::Component,
									public BeerEngine::Component::IUpdate,
									public BeerEngine::Component::IStart
		{
		public:

			// BeerRoutineTester( void );
			// BeerRoutineTester( BeerRoutineTester const & src );
			BeerRoutineTester(BeerEngine::GameObject *gameObject);

			virtual ~BeerRoutineTester( void );

			BeerRoutineTester & operator=( BeerRoutineTester const & rhs );
			friend std::ostream & operator<<(std::ostream & o, BeerRoutineTester const & i);

			virtual void start();
			virtual void update();
			virtual void fixedUpdate();

			void startRoutine(BeerEngine::BeerRoutine::BeerRoutine &routine);

			BeerEngine::BeerRoutine::BeerRoutine *currentRoutine;
			BeerEngine::BeerRoutine::BeerRoutine *testRoutine;

			void	testDisplay(std::string content);
			BeerEngine::BeerRoutine::BeerRoutine *createTestRoutine();
		};

	};

};

#endif
