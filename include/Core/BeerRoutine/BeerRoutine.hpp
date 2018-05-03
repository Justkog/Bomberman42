#ifndef BE_CORE_PHYSICS_HPP
#define BE_CORE_PHYSICS_HPP 1

#include "Core/Core.hpp"

namespace BeerEngine
{
	namespace BeerRoutine
	{
		class BeerRoutine
		{
		private:
			std::vector<std::function<bool (void)>> _actions;
			float	timer;
		public:

			BeerRoutine &addAction(std::function<bool (void)> action);
			BeerRoutine &addTimer(float seconds);

			static BeerRoutine &CreateRoutine();

			void	update();
		};
	}
}

#endif