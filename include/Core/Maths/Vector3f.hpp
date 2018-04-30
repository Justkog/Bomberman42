#ifndef BE_CORE_MATH_VECTOR3F_HPP
# define BE_CORE_MATH_VECTOR3F_HPP 1

#include "Vector2f.hpp"

namespace BeerEngine
{
	namespace Maths
	{
		class Vector3f {
		private:
			float	_data[3];
		public:
			Vector3f(void);
			Vector3f(float v);
			Vector3f(float x, float y, float z);
			Vector3f(Vector3f const &vec);
			Vector3f(Vector2f &vec, float z = 0.0f);

			Vector3f	&operator=(Vector3f const &rhs);
			float		&operator[](int index);
			Vector3f	operator+(Vector3f rhs);
			Vector3f	&operator+=(Vector3f rhs);
			Vector3f	operator-(Vector3f rhs);
			Vector3f	&operator-=(Vector3f rhs);
			Vector3f	operator*(Vector3f rhs);
			Vector3f	&operator*=(Vector3f rhs);
			Vector3f	operator/(Vector3f rhs);
			Vector3f	&operator/=(Vector3f rhs);

			Vector3f	operator+(float v);
			Vector3f	&operator+=(float v);
			Vector3f	operator-(float v);
			Vector3f	&operator-=(float v);
			Vector3f	operator*(float v);
			Vector3f	&operator*=(float v);
			Vector3f	operator/(float v);
			Vector3f	&operator/=(float v);

			float		getX(void);
			Vector3f	&setX(float v);
			float		getY(void);
			Vector3f	&setY(float v);
			float		getZ(void);
			Vector3f	&setZ(float v);
			Vector3f	&set(float x, float y, float z);
			Vector3f	&set(Vector3f &v);
			Vector3f	clone(void);
			double		lengthSqrt(void);
			double		length(void);
			Vector3f	&normalize(void);
			double		distanceSqrt(Vector3f rhs);
			double		distance(Vector3f rhs);
			double		dot(Vector3f rhs);

			Vector3f	cross(Vector3f &other);
			Vector3f	reflect(Vector3f &normal);
			Vector3f	refract(Vector3f &normal, float eta);

			Vector2f	xy();
			Vector2f	xz();
			Vector2f	yz();
		};
	}
}

#endif