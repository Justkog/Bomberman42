#include "Core/BeerRoutine/BeerRoutine.hpp"
#include "Core/Time.hpp"

namespace BeerEngine
{
	namespace BeerRoutine
	{
		BeerRoutine &BeerRoutine::addAction(std::function<bool (void)> action)
		{
			_actions.push_back(action);
			return *this;
		}

		BeerRoutine &BeerRoutine::addTimer(float seconds)
		{
			_actions.push_back([=] () {
				if (this->timer >= seconds)
					return true;
				else
					return false;
			});
			return *this;
		}

		BeerRoutine &BeerRoutine::CreateRoutine()
		{
			auto routine = new BeerRoutine();
			return *routine;
		}

		void	BeerRoutine::update()
		{
			std::cout << "routine udpate .." << "\n";
			
			this->timer += Time::GetDeltaTime();
			
			bool res = false;
			while (res)
			{
				if (_actions.size() > 0)
					res = _actions[0]();
				else
				{
					std::cout << "all routines actions done" << "\n";
					break;
				}
				if (res)
				{
					this->_actions.erase(_actions.begin());
					this->timer = 0;
				}
			}
		}
	}
}