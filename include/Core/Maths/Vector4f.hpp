#ifndef BE_CORE_MATH_VECTOR4F_HPP
# define BE_CORE_MATH_VECTOR4F_HPP 1

#include "Vector3f.hpp"

namespace BeerEngine
{
	namespace Maths
	{
		class Vector4f {
		private:
			float	_data[4];
		public:
			Vector4f(void);
			Vector4f(float x, float y, float z, float w = 1.0f);
			Vector4f(Vector4f const &vec);

			Vector4f	&operator=(Vector4f const &rhs);
			float		&operator[](int index);

			Vector3f	xyz(void);
		};
	}
}

#endif