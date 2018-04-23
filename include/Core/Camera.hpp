#ifndef BE_CORE_CAMERA_HPP
#define BE_CORE_CAMERA_HPP 1

#include "Core.hpp"
#include "Transform.hpp"

namespace BeerEngine
{
	class Camera {
	public:
		static Camera	*main;

		Transform	transform;
	};
}

#endif