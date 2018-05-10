#include "Core/Time.hpp"

namespace BeerEngine
{
    double   Time::_LastTime = glfwGetTime();
    double   Time::_DeltaTime = 0.0;
    double   Time::_TimeSinceStartup = 0.0;
    double   Time::gameSpeed = 1.0;

    void     Time::Update(void)
    {
        double now = glfwGetTime();
        _DeltaTime = (now - _LastTime) * gameSpeed;
        _LastTime = now;
		_TimeSinceStartup += _DeltaTime;
    }

    double   Time::GetDeltaTime(void)
    {
        return (_DeltaTime);
    }

	double   Time::GetTimeSinceStartup(void)
    {
        return (_TimeSinceStartup);
    }
}