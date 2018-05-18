#include "Core/BeerRoutine/ARoutineRunner.hpp"
#include "Core/BeerRoutine/BeerRoutine.hpp"
#include "Core/Time.hpp"


namespace BeerEngine
{
	namespace BeerRoutine
	{
		ARoutineRunner::ARoutineRunner()
		{}

		ARoutineRunner::ARoutineRunner(const ARoutineRunner &val)
		{
			*this = val;
		}
		
		ARoutineRunner &ARoutineRunner::operator=(const ARoutineRunner &val)
		{
			if (this != &val)
			{
				_currentRoutines.clear();
				for (int i = 0; i < val._currentRoutines.size(); i++)
					_currentRoutines.push_back(val._currentRoutines[i]);
			}
			return (*this);
		}

		ARoutineRunner::~ARoutineRunner()
		{}

		void ARoutineRunner::startRoutine(BeerEngine::BeerRoutine::BeerRoutine &routine)
		{
			// std::cout << "starting routine!" << "\n";
			_currentRoutines.push_back(&routine);
		}

		void ARoutineRunner::stopRoutine(BeerEngine::BeerRoutine::BeerRoutine *routine)
		{
			if (routine)
			{
				auto foundRoutine = std::find(_currentRoutines.begin(), _currentRoutines.end(), routine);
				if (foundRoutine != _currentRoutines.end())
					_currentRoutines.erase(foundRoutine);
				else
					std::cout << "trying to stop a non running routine!" << "\n";
			}
			else
				std::cout << "trying to stop a null routine!" << "\n";
		}

		std::vector<BeerEngine::BeerRoutine::BeerRoutine *> ARoutineRunner::getRunningRoutines()
		{
			return _currentRoutines;
		}


		void ARoutineRunner::update()
		{
			for (int i = 0; i < _currentRoutines.size(); i++)
			{
				auto cR = _currentRoutines[i];
				cR->update();
				if (!cR->hasActionsLeft())
				{
					_currentRoutines.erase(std::find(_currentRoutines.begin(), _currentRoutines.end(), cR));
					i--;
				}
			}
		}
	}
}