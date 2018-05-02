#include "Core/Mathf.hpp"

namespace BeerEngine
{
	float Mathf::Range(float min, float max)
	{
		return (((max - min) * ((float)rand() / RAND_MAX)) + min);
	}
}