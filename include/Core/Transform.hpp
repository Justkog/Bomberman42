#ifndef BE_CORE_TRANSFORM_HPP
#define BE_CORE_TRANSFORM_HPP 1

#include "Core.hpp"

namespace BeerEngine
{
    class Transform
	{
	public:
		Transform		*parent;
		Maths::Vector3f	position;
		Maths::Vector3f	rotation;
		Maths::Vector3f	scale;

		Transform();

		void		translate(Maths::Vector3f pos);
		void		translate(float x, float y, float z);

		// Maths::Vector3f		forward(void);
		// Maths::Vector3f		left(void);
		// Maths::Vector3f		right(void);
		// Maths::Vector3f		top(void);

		Maths::Matrix4x4	getMat4(bool isCamera = false);

	};
}

#endif