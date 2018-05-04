#include "Core/BeerRoutine/ARoutineRunner.hpp"
#include "Core/BeerRoutine/BeerRoutine.hpp"
#include "Core/Time.hpp"


namespace BeerEngine
{
	namespace BeerRoutine
	{
		void ARoutineRunner::startRoutine(BeerEngine::BeerRoutine::BeerRoutine &routine)
		{
			// std::cout << "starting routine!" << "\n";
			currentRoutines.push_back(&routine);
		}

		void ARoutineRunner::stopRoutine(BeerEngine::BeerRoutine::BeerRoutine *routine)
		{
			if (routine)
			{
				auto foundRoutine = std::find(currentRoutines.begin(), currentRoutines.end(), routine);
				if (foundRoutine != currentRoutines.end())
					currentRoutines.erase(foundRoutine);
				else
					std::cout << "trying to stop a non running routine!" << "\n";
			}
			else
				std::cout << "trying to stop a null routine!" << "\n";
		}

		std::vector<BeerEngine::BeerRoutine::BeerRoutine *> ARoutineRunner::getRunningRoutines()
		{
			return currentRoutines;
		}


		void ARoutineRunner::update()
		{
			for (int i = 0; i < currentRoutines.size(); i++)
			{
				auto cR = currentRoutines[i];
				cR->update();
				if (!cR->hasActionsLeft())
				{
					currentRoutines.erase(std::find(currentRoutines.begin(), currentRoutines.end(), cR));
					i--;
				}
			}
		}
	}
}