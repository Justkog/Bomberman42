#ifndef BE_CORE_MATH_MATRIX4X4_HPP
# define BE_CORE_MATH_MATRIX4X4_HPP 1

#include "Vector2f.hpp"
#include "Vector3f.hpp"
#include "Vector4f.hpp"

namespace BeerEngine
{
	namespace Maths
	{
		class Matrix4x4 {
		private:
			float	_data[16];
		public:
			Matrix4x4(void);
			Matrix4x4(Matrix4x4 const &vec);

			Matrix4x4	&operator=(Matrix4x4 const &rhs);
			float		&operator[](int index);
			// Matrix4x4	operator*(Matrix4x4 &rhs);
			Matrix4x4	operator*(Matrix4x4 rhs);
			Vector3f	operator*(Vector3f &rhs);
			Vector4f	operator*(Vector4f &rhs);

			Vector3f	transform(Vector3f &v);
			Vector4f	transform(Vector4f &v);
			float		determinant(void);
			Matrix4x4	invert(void);

			// STATIC
			static Matrix4x4	Identity(void);
			static Matrix4x4	Translate(float x, float y, float z);
			static Matrix4x4	Translate(Vector2f rhs);
			static Matrix4x4	Translate(Vector3f rhs);
			static Matrix4x4	Scale(float x, float y, float z);
			static Matrix4x4	Scale(Vector2f rhs);
			static Matrix4x4	Scale(Vector3f rhs);
			static Matrix4x4	RotateX(float r);
			static Matrix4x4	RotateY(float r);
			static Matrix4x4	RotateZ(float r);
			static Matrix4x4	Euler(float x, float y, float z);
			static Matrix4x4	Euler(Vector3f rhs);
			static Matrix4x4	Perspective(float fov, float aspect, float zNear, float zFar);
			static Matrix4x4	Orthographic(float left, float right, float bottom, float top, float zNear, float zFar);

			static float		Determinant3x3(float t00, float t01, float t02, float t10, float t11, float t12, float t20, float t21, float t22);
		};
	}
}

#endif