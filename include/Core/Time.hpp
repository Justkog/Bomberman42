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
    
    public:
        static void     Update(void);
        static double   GetDeltaTime(void);
    };
}

#endif