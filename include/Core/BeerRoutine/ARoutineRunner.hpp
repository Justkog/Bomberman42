#ifndef BE_CORE_AROUTINE_RUNNER_HPP
#define BE_CORE_AROUTINE_RUNNER_HPP 1

#include "Core/Core.hpp"

namespace BeerEngine
{
	namespace BeerRoutine
	{
		class ARoutineRunner
		{
		public:
			virtual void update();

			void startRoutine(BeerEngine::BeerRoutine::BeerRoutine &routine);
			void stopRoutine(BeerEngine::BeerRoutine::BeerRoutine *routine);
			std::vector<BeerEngine::BeerRoutine::BeerRoutine *> getRunningRoutines();

			std::vector<BeerEngine::BeerRoutine::BeerRoutine *> currentRoutines;

		};
	}
}

#endif