#include <cmath>
#include "Core/Maths/Vector2f.hpp"

namespace BeerEngine
{
	namespace Maths
	{
		Vector2f::Vector2f(void)
		{
			_data[0] = 0.0f;
			_data[1] = 0.0f;
		}

		Vector2f::Vector2f(float v)
		{
			_data[0] = v;
			_data[1] = v;
		}

		Vector2f::Vector2f(float x, float y)
		{
			_data[0] = x;
			_data[1] = y;
		}

		Vector2f::Vector2f(Vector2f const &vec)
		{
			*this = vec;
		}

		Vector2f	&Vector2f::operator=(Vector2f const &rhs)
		{
			_data[0] = rhs._data[0];
			_data[1] = rhs._data[1];
			return (*this);
		}

		float		&Vector2f::operator[](int index)
		{
			return (_data[index]);
		}

		Vector2f	Vector2f::operator+(Vector2f rhs)
		{
			return (Vector2f(_data[0] + rhs[0], _data[1] + rhs[1]));
		}

		Vector2f	&Vector2f::operator+=(Vector2f rhs)
		{
			_data[0] += rhs[0];
			_data[1] += rhs[1];
			return (*this);
		}

		Vector2f	Vector2f::operator-(Vector2f rhs)
		{
			return (Vector2f(_data[0] - rhs[0], _data[1] - rhs[1]));
		}

		Vector2f	&Vector2f::operator-=(Vector2f rhs)
		{
			_data[0] -= rhs[0];
			_data[1] -= rhs[1];
			return (*this);
		}

		Vector2f	Vector2f::operator*(Vector2f rhs)
		{
			return (Vector2f(_data[0] * rhs[0], _data[1] * rhs[1]));
		}

		Vector2f	&Vector2f::operator*=(Vector2f rhs)
		{
			_data[0] *= rhs[0];
			_data[1] *= rhs[1];
			return (*this);
		}

		Vector2f	Vector2f::operator/(Vector2f rhs)
		{
			return (Vector2f(_data[0] / rhs[0], _data[1] / rhs[1]));
		}

		Vector2f	&Vector2f::operator/=(Vector2f rhs)
		{
			_data[0] /= rhs[0];
			_data[1] /= rhs[1];
			return (*this);
		}

		Vector2f	Vector2f::operator+(float v)
		{
			return (Vector2f(_data[0] + v, _data[1] + v));
		}

		Vector2f	&Vector2f::operator+=(float v)
		{
			_data[0] += v;
			_data[1] += v;
			return (*this);
		}

		Vector2f	Vector2f::operator-(float v)
		{
			return (Vector2f(_data[0] - v, _data[1] - v));
		}

		Vector2f	&Vector2f::operator-=(float v)
		{
			_data[0] -= v;
			_data[1] -= v;
			return (*this);
		}

		Vector2f	Vector2f::operator*(float v)
		{
			return (Vector2f(_data[0] * v, _data[1] * v));
		}

		Vector2f	&Vector2f::operator*=(float v)
		{
			_data[0] *= v;
			_data[1] *= v;
			return (*this);
		}

		Vector2f	Vector2f::operator/(float v)
		{
			return (Vector2f(_data[0] / v, _data[1] / v));
		}

		Vector2f	&Vector2f::operator/=(float v)
		{
			_data[0] /= v;
			_data[1] /= v;
			return (*this);
		}

		float		Vector2f::getX(void)
		{
			return (_data[0]);
		}

		Vector2f	&Vector2f::setX(float v)
		{
			_data[0] = v;
			return (*this);
		}

		float		Vector2f::getY(void)
		{
			return (_data[1]);
		}

		Vector2f	&Vector2f::setY(float v)
		{
			_data[1] = v;
			return (*this);
		}

		Vector2f	&Vector2f::set(float x, float y)
		{
			_data[0] = x;
			_data[1] = y;
			return (*this);
		}

		Vector2f	&Vector2f::set(Vector2f &vec)
		{
			_data[0] = vec[0];
			_data[1] = vec[1];
			return (*this);
		}

		Vector2f	Vector2f::clone(void)
		{
			return (Vector2f(*this));
		}

		Vector2f	&Vector2f::rotate(double rad)
		{
			double c = std::cos(rad);
			double s = std::sin(rad);
			double tx = _data[0] * c - _data[1] * s;
			double ty = _data[0] * s + _data[1] * c;
			return (set(tx, ty));
		}

		double		Vector2f::lengthSqrt(void)
		{
			return (_data[0] * _data[0] + _data[1] * _data[1]);
		}

		double		Vector2f::length(void)
		{
			return (std::sqrt(lengthSqrt()));
		}

		Vector2f	&Vector2f::normalize(void)
		{
			float len = length();
			_data[0] /= len;
			_data[1] /= len;
			return (*this);
		}

		double		Vector2f::distanceSqrt(Vector2f rhs)
		{
			Vector2f v = rhs - *this;
			return (v.lengthSqrt());
		}

		double		Vector2f::distance(Vector2f rhs)
		{
			Vector2f v = rhs - *this;
			return (v.length());
		}

		double		Vector2f::dot(Vector2f rhs)
		{
			return (_data[0] * rhs[0] + _data[1] * rhs[1]);
		}

		Vector2f	Vector2f::normal(void)
		{
			return (Vector2f(-_data[1], _data[0]));
		}
	}
}