#include "Core/Time.hpp"

namespace BeerEngine
{
    double   Time::_LastTime = glfwGetTime();
    double   Time::_DeltaTime = 0.0;

    void     Time::Update(void)
    {
        double now = glfwGetTime();
        _DeltaTime = now - _LastTime;
        _LastTime = now;
    }

    double   Time::GetDeltaTime(void)
    {
        return (_DeltaTime);
    }

}