#include "Core/Maths/Maths.hpp"

namespace BeerEngine
{
	namespace Maths
	{
		Matrix4x4::Matrix4x4(void)
		{
			for (int i = 0; i < 16; i++)
				_data[i] = 0.0f;
		}

		Matrix4x4::Matrix4x4(Matrix4x4 const &vec)
		{
			*this = vec;
		}

		Matrix4x4	&Matrix4x4::operator=(Matrix4x4 const &rhs)
		{
			for (int i = 0; i < 16; i++)
				_data[i] = rhs._data[i];
			return (*this);
		}

		float		&Matrix4x4::operator[](int index)
		{
			return (_data[index]);
		}

		// Matrix4x4	Matrix4x4::operator*(Matrix4x4 &rhs)
		// {
		// 	Matrix4x4 mat;
		// 	for (int i = 0; i < 4; i++)
        //     	for (int j = 0; j < 4; j++)
        //         	for (int k = 0; k < 4; k++)
        //            		mat[i + j * 4] += _data[k + j * 4] * rhs[i + k * 4];
		// 	return (mat);
		// }
		Matrix4x4	Matrix4x4::operator*(Matrix4x4 rhs)
		{
			Matrix4x4 mat;
			for (int i = 0; i < 4; i++)
            	for (int j = 0; j < 4; j++)
                	for (int k = 0; k < 4; k++)
                   		mat[i + j * 4] += rhs[k + j * 4] * _data[i + k * 4];
			return (mat);
		}

		Vector3f	Matrix4x4::operator*(Vector3f &rhs)
		{
			return (transform(rhs));
		}


		Vector4f	Matrix4x4::operator*(Vector4f &rhs)
		{
			return (transform(rhs));
		}

		Vector3f	Matrix4x4::transform(Vector3f &v)
		{
			return (Vector3f(
				_data[0] * v[0] + _data[4] * v[1] + _data[8] * v[2] + _data[12],
				_data[1] * v[0] + _data[5] * v[1] + _data[9] * v[2] + _data[13],
				_data[2] * v[0] + _data[6] * v[1] + _data[10] * v[2] + _data[14]
			));
		}

		Vector4f	Matrix4x4::transform(Vector4f &v)
		{
			return (Vector4f(
				_data[0 + 0 * 4] * v[0] + _data[0 + 1 * 4] * v[1] + _data[0 + 2 * 4] * v[2] + _data[0 + 3 * 4] * v[3],
				_data[1 + 0 * 4] * v[0] + _data[1 + 1 * 4] * v[1] + _data[1 + 2 * 4] * v[2] + _data[1 + 3 * 4] * v[3],
				_data[2 + 0 * 4] * v[0] + _data[2 + 1 * 4] * v[1] + _data[2 + 2 * 4] * v[2] + _data[2 + 3 * 4] * v[3],
				v[3]
			));
		}
		
		float		Matrix4x4::determinant(void)
		{
			float f = _data[0 + 0 * 4] * ((_data[1 + 1 * 4] * _data[2 + 2 * 4] * _data[3 + 3 * 4] + _data[1 + 2 * 4] * _data[2 + 3 * 4] * _data[3 + 1 * 4] + _data[1 + 3 * 4] * _data[2 + 1 * 4] * _data[3 + 2 * 4])
					- _data[1 + 3 * 4] * _data[2 + 2 * 4] * _data[3 + 1 * 4]
					- _data[1 + 1 * 4] * _data[2 + 3 * 4] * _data[3 + 2 * 4]
					- _data[1 + 2 * 4] * _data[2 + 1 * 4] * _data[3 + 3 * 4]);
			f -= _data[0 + 1 * 4] * ((_data[1 + 0 * 4] * _data[2 + 2 * 4] * _data[3 + 3 * 4] + _data[1 + 2 * 4] * _data[2 + 3 * 4] * _data[3 + 0 * 4] + _data[1 + 3 * 4] * _data[2 + 0 * 4] * _data[3 + 2 * 4])
					- _data[1 + 3 * 4] * _data[2 + 2 * 4] * _data[3 + 0 * 4]
					- _data[1 + 0 * 4] * _data[2 + 3 * 4] * _data[3 + 2 * 4]
					- _data[1 + 2 * 4] * _data[2 + 0 * 4] * _data[3 + 3 * 4]);
			f += _data[0 + 2 * 4] * ((_data[1 + 0 * 4] * _data[2 + 1 * 4] * _data[3 + 3 * 4] + _data[1 + 1 * 4] * _data[2 + 3 * 4] * _data[3 + 0 * 4] + _data[1 + 3 * 4] * _data[2 + 0 * 4] * _data[3 + 1 * 4])
					- _data[1 + 3 * 4] * _data[2 + 1 * 4] * _data[3 + 0 * 4]
					- _data[1 + 0 * 4] * _data[2 + 3 * 4] * _data[3 + 1 * 4]
					- _data[1 + 1 * 4] * _data[2 + 0 * 4] * _data[3 + 3 * 4]);
			f -= _data[0 + 3 * 4] * ((_data[1 + 0 * 4] * _data[2 + 1 * 4] * _data[3 + 2 * 4] + _data[1 + 1 * 4] * _data[2 + 2 * 4] * _data[3 + 0 * 4] + _data[1 + 2 * 4] * _data[2 + 0 * 4] * _data[3 + 1 * 4])
					- _data[1 + 2 * 4] * _data[2 + 1 * 4] * _data[3 + 0 * 4]
					- _data[1 + 0 * 4] * _data[2 + 2 * 4] * _data[3 + 1 * 4]
					- _data[1 + 1 * 4] * _data[2 + 0 * 4] * _data[3 + 2 * 4]);
			return (f);
		}

		Matrix4x4	Matrix4x4::invert(void)
		{
			Matrix4x4 mat;
			float determinant = this->determinant();

			if (determinant != 0) {
				float determinant_inv = 1.0f / determinant;

				float t00 =  Determinant3x3(_data[1 + 1 * 4], _data[1 + 2 * 4], _data[1 + 3 * 4], _data[2 + 1 * 4], _data[2 + 2 * 4], _data[2 + 3 * 4], _data[3 + 1 * 4], _data[3 + 2 * 4], _data[3 + 3 * 4]);
				float t01 = -Determinant3x3(_data[1 + 0 * 4], _data[1 + 2 * 4], _data[1 + 3 * 4], _data[2 + 0 * 4], _data[2 + 2 * 4], _data[2 + 3 * 4], _data[3 + 0 * 4], _data[3 + 2 * 4], _data[3 + 3 * 4]);
				float t02 =  Determinant3x3(_data[1 + 0 * 4], _data[1 + 1 * 4], _data[1 + 3 * 4], _data[2 + 0 * 4], _data[2 + 1 * 4], _data[2 + 3 * 4], _data[3 + 0 * 4], _data[3 + 1 * 4], _data[3 + 3 * 4]);
				float t03 = -Determinant3x3(_data[1 + 0 * 4], _data[1 + 1 * 4], _data[1 + 2 * 4], _data[2 + 0 * 4], _data[2 + 1 * 4], _data[2 + 2 * 4], _data[3 + 0 * 4], _data[3 + 1 * 4], _data[3 + 2 * 4]);
				
				float t10 = -Determinant3x3(_data[0 + 1 * 4], _data[0 + 2 * 4], _data[0 + 3 * 4], _data[2 + 1 * 4], _data[2 + 2 * 4], _data[2 + 3 * 4], _data[3 + 1 * 4], _data[3 + 2 * 4], _data[3 + 3 * 4]);
				float t11 =  Determinant3x3(_data[0 + 0 * 4], _data[0 + 2 * 4], _data[0 + 3 * 4], _data[2 + 0 * 4], _data[2 + 2 * 4], _data[2 + 3 * 4], _data[3 + 0 * 4], _data[3 + 2 * 4], _data[3 + 3 * 4]);
				float t12 = -Determinant3x3(_data[0 + 0 * 4], _data[0 + 1 * 4], _data[0 + 3 * 4], _data[2 + 0 * 4], _data[2 + 1 * 4], _data[2 + 3 * 4], _data[3 + 0 * 4], _data[3 + 1 * 4], _data[3 + 3 * 4]);
				float t13 =  Determinant3x3(_data[0 + 0 * 4], _data[0 + 1 * 4], _data[0 + 2 * 4], _data[2 + 0 * 4], _data[2 + 1 * 4], _data[2 + 2 * 4], _data[3 + 0 * 4], _data[3 + 1 * 4], _data[3 + 2 * 4]);
				
				float t20 =  Determinant3x3(_data[0 + 1 * 4], _data[0 + 2 * 4], _data[0 + 3 * 4], _data[1 + 1 * 4], _data[1 + 2 * 4], _data[1 + 3 * 4], _data[3 + 1 * 4], _data[3 + 2 * 4], _data[3 + 3 * 4]);
				float t21 = -Determinant3x3(_data[0 + 0 * 4], _data[0 + 2 * 4], _data[0 + 3 * 4], _data[1 + 0 * 4], _data[1 + 2 * 4], _data[1 + 3 * 4], _data[3 + 0 * 4], _data[3 + 2 * 4], _data[3 + 3 * 4]);
				float t22 =  Determinant3x3(_data[0 + 0 * 4], _data[0 + 1 * 4], _data[0 + 3 * 4], _data[1 + 0 * 4], _data[1 + 1 * 4], _data[1 + 3 * 4], _data[3 + 0 * 4], _data[3 + 1 * 4], _data[3 + 3 * 4]);
				float t23 = -Determinant3x3(_data[0 + 0 * 4], _data[0 + 1 * 4], _data[0 + 2 * 4], _data[1 + 0 * 4], _data[1 + 1 * 4], _data[1 + 2 * 4], _data[3 + 0 * 4], _data[3 + 1 * 4], _data[3 + 2 * 4]);

				float t30 = -Determinant3x3(_data[0 + 1 * 4], _data[0 + 2 * 4], _data[0 + 3 * 4], _data[1 + 1 * 4], _data[1 + 2 * 4], _data[1 + 3 * 4], _data[2 + 1 * 4], _data[2 + 2 * 4], _data[2 + 3 * 4]);
				float t31 =  Determinant3x3(_data[0 + 0 * 4], _data[0 + 2 * 4], _data[0 + 3 * 4], _data[1 + 0 * 4], _data[1 + 2 * 4], _data[1 + 3 * 4], _data[2 + 0 * 4], _data[2 + 2 * 4], _data[2 + 3 * 4]);
				float t32 = -Determinant3x3(_data[0 + 0 * 4], _data[0 + 1 * 4], _data[0 + 3 * 4], _data[1 + 0 * 4], _data[1 + 1 * 4], _data[1 + 3 * 4], _data[2 + 0 * 4], _data[2 + 1 * 4], _data[2 + 3 * 4]);
				float t33 =  Determinant3x3(_data[0 + 0 * 4], _data[0 + 1 * 4], _data[0 + 2 * 4], _data[1 + 0 * 4], _data[1 + 1 * 4], _data[1 + 2 * 4], _data[2 + 0 * 4], _data[2 + 1 * 4], _data[2 + 2 * 4]);

				mat[0 + 0 * 4] = t00 * determinant_inv;
				mat[1 + 1 * 4] = t11 * determinant_inv;
				mat[2 + 2 * 4] = t22 * determinant_inv;
				mat[3 + 3 * 4] = t33 * determinant_inv;
				mat[0 + 1 * 4] = t10 * determinant_inv;
				mat[1 + 0 * 4] = t01 * determinant_inv;
				mat[2 + 0 * 4] = t02 * determinant_inv;
				mat[0 + 2 * 4] = t20 * determinant_inv;
				mat[1 + 2 * 4] = t21 * determinant_inv;
				mat[2 + 1 * 4] = t12 * determinant_inv;
				mat[0 + 3 * 4] = t30 * determinant_inv;
				mat[3 + 0 * 4] = t03 * determinant_inv;
				mat[1 + 3 * 4] = t31 * determinant_inv;
				mat[3 + 1 * 4] = t13 * determinant_inv;
				mat[3 + 2 * 4] = t23 * determinant_inv;
				mat[2 + 3 * 4] = t32 * determinant_inv;
			}
			return (mat);
		}


		/* ********** */
		/* * STATIC * */
		/* ********** */

		Matrix4x4	Matrix4x4::Identity(void)
		{
			Matrix4x4 mat;
			mat[0] = 1.0f;
			mat[5] = 1.0f;
			mat[10] = 1.0f;
			mat[15] = 1.0f;
			return (mat);
		}

		Matrix4x4	Matrix4x4::Translate(float x, float y, float z)
		{
			Matrix4x4 mat = Identity();
			mat[12] = x;
			mat[13] = y;
			mat[14] = z;
			return (mat);
		}

		Matrix4x4	Matrix4x4::Translate(Vector2f rhs)
		{
			return (Translate(rhs[0], rhs[1], 0.0f));
		}

		Matrix4x4	Matrix4x4::Translate(Vector3f rhs)
		{
			return (Translate(rhs[0], rhs[1], rhs[2]));
		}

		Matrix4x4	Matrix4x4::Scale(float x, float y, float z)
		{
			Matrix4x4 mat = Identity();
			mat[0] = x;
			mat[5] = y;
			mat[10] = z;
			return (mat);
		}

		Matrix4x4	Matrix4x4::Scale(Vector2f rhs)
		{
			return (Scale(rhs[0], rhs[1], 0.0f));
		}

		Matrix4x4	Matrix4x4::Scale(Vector3f rhs)
		{
			return (Scale(rhs[0], rhs[1], rhs[2]));
		}

		Matrix4x4	Matrix4x4::RotateX(float r)
		{
			Matrix4x4 mat = Identity();
			float rcos = cosf(r);
			float rsin = sinf(r);
			mat[5] = rcos;
			mat[6] = rsin;
			mat[9] = -rsin;
			mat[10] = rcos;
			return (mat);
		}

		Matrix4x4	Matrix4x4::RotateY(float r)
		{
			Matrix4x4 mat = Identity();
			float rcos = cosf(r);
			float rsin = sinf(r);
			mat[0] = rcos;
			mat[2] = rsin;
			mat[8] = -rsin;
			mat[10] = rcos;
			return (mat);
		}

		Matrix4x4	Matrix4x4::RotateZ(float r)
		{
			Matrix4x4 mat = Identity();
			float rcos = cosf(r);
			float rsin = sinf(r);
			mat[0] = rcos;
			mat[1] = rsin;
			mat[4] = -rsin;
			mat[5] = rcos;
			return (mat);
		}

		Matrix4x4	Matrix4x4::Euler(float x, float y, float z)
		{
			Matrix4x4 mat = Identity();
			float xcos = (float)std::cos(x);
			float xsin = (float)std::sin(x);
			float ycos = (float)std::cos(y);
			float ysin = (float)std::sin(y);
			float zcos = (float)std::cos(z);
			float zsin = (float)std::sin(z);
			float xcys = xcos * ysin;
			float xsys = xsin * ysin;
			mat[0 + 0 * 4] = ycos * zcos;
			mat[1 + 0 * 4] = -ycos * zsin;
			mat[2 + 0 * 4] = ysin;
			mat[0 + 1 * 4] = xsys * zcos + xcos * zsin;
			mat[1 + 1 * 4] = -xsys * zsin + xcos * zcos;
			mat[2 + 1 * 4] = -xsin * ycos;
			mat[0 + 2 * 4] = -xcys * zcos + xsin * zsin;
			mat[1 + 2 * 4] = xcys * zsin + xsin * zcos;
			mat[2 + 2 * 4] = xcos * ycos;
			return (mat);
		}

		Matrix4x4	Matrix4x4::Euler(Vector3f rhs)
		{
			return (Euler(rhs[0], rhs[1], rhs[2]));
		}

		Matrix4x4	Matrix4x4::Perspective(float fov, float aspect, float zNear, float zFar)
		{
			Matrix4x4 mat;
			fov = std::tanf(fov / 2.f);
			float dist = zNear - zFar;
			mat[0] = 1.f / (fov * aspect);
			mat[5] = 1.f / fov;
			mat[10] = (-zNear - zFar) / dist;
			mat[11] = 1.f;
			mat[14] = 2.f * zFar * zNear / dist;
			return (mat);
		}

		Matrix4x4	Matrix4x4::Orthographic(float left, float right, float bottom, float top, float zNear, float zFar)
		{
			Matrix4x4 mat = Identity();
			mat[0] = 2.f / (right - left);
			mat[5] = 2.f / (top - bottom);
			mat[10] = -2.f / (zFar - zNear);
			mat[12] = -(right + left) / (right - left);
			mat[13] = -(top + bottom) / (top - bottom);
			mat[14] = -(zFar + zNear) / (zFar - zNear);
			return (mat);
		}

		float		Matrix4x4::Determinant3x3(float t00, float t01, float t02, float t10, float t11, float t12, float t20, float t21, float t22)
		{
			return (t00 * (t11 * t22 - t12 * t21) + t01 * (t12 * t20 - t10 * t22) + t02 * (t10 * t21 - t11 * t20));
		}
	}
}