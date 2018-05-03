#include "Core/BeerRoutine/BeerRoutine.hpp"
#include "Core/Time.hpp"

namespace BeerEngine
{
	namespace BeerRoutine
	{
		BeerRoutine::BeerRoutine()
		{
			_loop = false;
		}

		BeerRoutine &BeerRoutine::addAction(std::function<bool (void)> action)
		{
			_actions.push_back(action);
			return *this;
		}

		BeerRoutine &BeerRoutine::addTimer(float seconds)
		{
			_actions.push_back([=] () {
				if (this->_timer >= seconds)
					return true;
				else
					return false;
			});
			return *this;
		}

		BeerRoutine &BeerRoutine::loop()
		{
			_loop = true;
			return *this;
		}

		BeerRoutine &BeerRoutine::CreateRoutine()
		{
			auto routine = new BeerRoutine();
			return *routine;
		}

		bool	BeerRoutine::hasActionsLeft()
		{
			return (_actions.size() > 0);
		}


		void	BeerRoutine::update()
		{
			this->_timer += Time::GetDeltaTime();
			
			bool res = true;
			while (res)
			{
				if (_actions.size() > 0)
					res = _actions[0]();
				else
				{
					break;
				}
				if (res)
				{
					if (_loop)
						this->_actions.push_back(_actions[0]);
					this->_actions.erase(_actions.begin());
					this->_timer = 0;
				}
			}
		}
	}
}