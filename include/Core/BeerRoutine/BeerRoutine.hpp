#ifndef BE_CORE_BEER_ROUTINE_HPP
#define BE_CORE_BEER_ROUTINE_HPP 1

#include "Core/Core.hpp"

namespace BeerEngine
{
	namespace BeerRoutine
	{
		class BeerRoutine
		{
		private:
			std::vector<std::function<bool (void)>> _actions;
			float	_timer;
			bool	_loop;
		public:

			BeerRoutine();
			BeerRoutine &addAction(std::function<bool (void)> action);
			BeerRoutine &addTimer(float seconds);
			BeerRoutine &loop();

			static BeerRoutine &CreateRoutine();

			void	update();
			bool	hasActionsLeft();
		};
	}
}

#endif