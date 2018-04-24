#include <cmath>
#include "Core/Maths/Vector3f.hpp"

namespace BeerEngine
{
	namespace Maths
	{
		Vector3f::Vector3f(void)
		{
			_data[0] = 0.0f;
			_data[1] = 0.0f;
			_data[2] = 0.0f;
		}

		Vector3f::Vector3f(float v)
		{
			_data[0] = v;
			_data[1] = v;
			_data[2] = v;
		}

		Vector3f::Vector3f(float x, float y, float z)
		{
			_data[0] = x;
			_data[1] = y;
			_data[2] = z;
		}

		Vector3f::Vector3f(Vector3f const &vec)
		{
			*this = vec;
		}

		Vector3f::Vector3f(Vector2f &vec, float z)
		{
			_data[0] = vec.getX();
			_data[1] = vec.getY();
			_data[2] = z;
		}

		Vector3f	&Vector3f::operator=(Vector3f const &rhs)
		{
			_data[0] = rhs._data[0];
			_data[1] = rhs._data[1];
			_data[2] = rhs._data[2];
			return (*this);
		}

		float		&Vector3f::operator[](int index)
		{
			return (_data[index]);
		}

		Vector3f	Vector3f::operator+(Vector3f rhs)
		{
			return (Vector3f(_data[0] + rhs[0], _data[1] + rhs[1], _data[2] + rhs[2]));
		}

		Vector3f	&Vector3f::operator+=(Vector3f rhs)
		{
			_data[0] += rhs[0];
			_data[1] += rhs[1];
			_data[2] += rhs[2];
			return (*this);
		}

		Vector3f	Vector3f::operator-(Vector3f rhs)
		{
			return (Vector3f(_data[0] - rhs[0], _data[1] - rhs[1], _data[2] - rhs[2]));
		}

		Vector3f	&Vector3f::operator-=(Vector3f rhs)
		{
			_data[0] -= rhs[0];
			_data[1] -= rhs[1];
			_data[2] -= rhs[2];
			return (*this);
		}

		Vector3f	Vector3f::operator*(Vector3f rhs)
		{
			return (Vector3f(_data[0] * rhs[0], _data[1] * rhs[1], _data[2] * rhs[2]));
		}

		Vector3f	&Vector3f::operator*=(Vector3f rhs)
		{
			_data[0] *= rhs[0];
			_data[1] *= rhs[1];
			_data[2] *= rhs[2];
			return (*this);
		}

		Vector3f	Vector3f::operator/(Vector3f rhs)
		{
			return (Vector3f(_data[0] / rhs[0], _data[1] / rhs[1], _data[2] / rhs[2]));
		}

		Vector3f	&Vector3f::operator/=(Vector3f rhs)
		{
			_data[0] /= rhs[0];
			_data[1] /= rhs[1];
			_data[2] /= rhs[2];
			return (*this);
		}

		Vector3f	Vector3f::operator+(float v)
		{
			return (Vector3f(_data[0] + v, _data[1] + v, _data[2] + v));
		}

		Vector3f	&Vector3f::operator+=(float v)
		{
			_data[0] += v;
			_data[1] += v;
			_data[2] += v;
			return (*this);
		}

		Vector3f	Vector3f::operator-(float v)
		{
			return (Vector3f(_data[0] - v, _data[1] - v, _data[2] - v));
		}

		Vector3f	&Vector3f::operator-=(float v)
		{
			_data[0] -= v;
			_data[1] -= v;
			_data[2] -= v;
			return (*this);
		}

		Vector3f	Vector3f::operator*(float v)
		{
			return (Vector3f(_data[0] * v, _data[1] * v, _data[2] * v));
		}

		Vector3f	&Vector3f::operator*=(float v)
		{
			_data[0] *= v;
			_data[1] *= v;
			_data[2] *= v;
			return (*this);
		}

		Vector3f	Vector3f::operator/(float v)
		{
			return (Vector3f(_data[0] / v, _data[1] / v, _data[2] / v));
		}

		Vector3f	&Vector3f::operator/=(float v)
		{
			_data[0] /= v;
			_data[1] /= v;
			_data[2] /= v;
			return (*this);
		}

		float		Vector3f::getX(void)
		{
			return (_data[0]);
		}

		Vector3f	&Vector3f::setX(float v)
		{
			_data[0] = v;
			return (*this);
		}

		float		Vector3f::getY(void)
		{
			return (_data[1]);
		}

		Vector3f	&Vector3f::setY(float v)
		{
			_data[1] = v;
			return (*this);
		}

		float		Vector3f::getZ(void)
		{
			return (_data[2]);
		}

		Vector3f	&Vector3f::setZ(float v)
		{
			_data[2] = v;
			return (*this);
		}

		Vector3f	&Vector3f::set(float x, float y, float z)
		{
			_data[0] = x;
			_data[1] = y;
			_data[2] = z;
			return (*this);
		}

		Vector3f	&Vector3f::set(Vector3f &v)
		{
			return (set(v[0], v[1], v[2]));
		}

		Vector3f	Vector3f::clone(void)
		{
			return (Vector3f(*this));
		}

		double		Vector3f::lengthSqrt(void)
		{
			return (_data[0] * _data[0] + _data[1] * _data[1] + _data[2] * _data[2]);
		}

		double		Vector3f::length(void)
		{
			return (std::sqrt(lengthSqrt()));
		}

		Vector3f	&Vector3f::normalize(void)
		{
			float len = length();
			_data[0] /= len;
			_data[1] /= len;
			_data[2] /= len;
			return (*this);
		}

		double		Vector3f::distanceSqrt(Vector3f rhs)
		{
			Vector3f v = rhs - *this;
			return (v.lengthSqrt());
		}

		double		Vector3f::distance(Vector3f rhs)
		{
			Vector3f v = rhs - *this;
			return (v.length());
		}

		double		Vector3f::dot(Vector3f rhs)
		{
			return (_data[0] * rhs[0] + _data[1] * rhs[1] + _data[2] * rhs[2]);
		}

		Vector3f	Vector3f::cross(Vector3f &other)
		{
			return (Vector3f(
				getY() * other.getZ() - getZ() * other.getY(),
				getZ() * other.getX() - getX() * other.getZ(),
				getX() * other.getY() - getY() * other.getX()
			));
		}

		Vector3f	Vector3f::reflect(Vector3f &normal)
		{
			float f = (float)this->dot(normal) * 2.0f;
			Vector3f n = normal * f;
			return (*this * n);
		}

		Vector3f	Vector3f::refract(Vector3f &normal, float eta)
		{
			float d = normal.dot(*this);
			float k = 1.f - eta * eta * (1.f - d * d);
			if (k < 0.f)
				return (Vector3f());
			float m = eta * d + sqrtf(k);
			Vector3f t = (*this * eta);
			t -= m;
			return (normal * t);
		}

		Vector2f	Vector3f::xy()
		{
			return (Vector2f(getX(), getY()));
		}

		Vector2f	Vector3f::xz()
		{
			return (Vector2f(getX(), getZ()));
		}

		Vector2f	Vector3f::yz()
		{
			return (Vector2f(getY(), getZ()));
		}

	}
}