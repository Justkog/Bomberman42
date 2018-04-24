#ifndef BE_CORE_MATH_OPERATOR_HPP
# define BE_CORE_MATH_OPERATOR_HPP 1

#include <iostream>
#include "Maths.hpp"

namespace BeerEngine
{
	namespace Maths
	{
		std::ostream	&operator<<(std::ostream &os, Vector2f &rhs);
		std::ostream	&operator<<(std::ostream &os, Vector3f &rhs);
		std::ostream	&operator<<(std::ostream &os, Matrix4x4 &rhs);
	}
}
#endif