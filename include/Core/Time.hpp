#ifndef BE_CORE_TIMER_HPP
#define BE_CORE_TIMER_HPP 1

#include "Core.hpp"

namespace BeerEngine
{
    class Time
    {
    private:
        static double   _LastTime;
        static double   _DeltaTime;
        static double   _TimeSinceStartup;
    
    public:
        static double   gameSpeed;
		
        static void     Update(void);
        static double   GetDeltaTime(void);
		static double   GetTimeSinceStartup(void);

    };
}

#endif