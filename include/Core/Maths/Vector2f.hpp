#ifndef BE_CORE_MATH_VECTOR2F_HPP
# define BE_CORE_MATH_VECTOR2F_HPP 1

namespace BeerEngine
{
	namespace Maths
	{
		class Vector2f {
		private:
			float	_data[2];
		public:
			Vector2f(void);
			Vector2f(float v);
			Vector2f(float x, float y);
			Vector2f(Vector2f const &vec);

			Vector2f	&operator=(Vector2f const &rhs);
			float		&operator[](int index);
			Vector2f	operator+(Vector2f rhs);
			Vector2f	&operator+=(Vector2f rhs);
			Vector2f	operator-(Vector2f rhs);
			Vector2f	&operator-=(Vector2f rhs);
			Vector2f	operator*(Vector2f rhs);
			Vector2f	&operator*=(Vector2f rhs);
			Vector2f	operator/(Vector2f rhs);
			Vector2f	&operator/=(Vector2f rhs);

			Vector2f	operator+(float v);
			Vector2f	&operator+=(float v);
			Vector2f	operator-(float v);
			Vector2f	&operator-=(float v);
			Vector2f	operator*(float v);
			Vector2f	&operator*=(float v);
			Vector2f	operator/(float v);
			Vector2f	&operator/=(float v);

			float		getX(void);
			Vector2f	&setX(float v);
			float		getY(void);
			Vector2f	&setY(float v);
			Vector2f	&set(float x, float y);
			Vector2f	&set(Vector2f &v);
			Vector2f	clone(void);
			Vector2f	&rotate(double rad);
			double		lengthSqrt(void);
			double		length(void);
			Vector2f	&normalize(void);
			double		distanceSqrt(Vector2f rhs);
			double		distance(Vector2f rhs);
			double		dot(Vector2f rhs);
			Vector2f	normal(void);
		};
	}
}

#endif