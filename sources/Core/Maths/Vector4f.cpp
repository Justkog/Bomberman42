#include "Core/Maths/Vector4f.hpp"

namespace BeerEngine
{
	namespace Maths
	{
		Vector4f::Vector4f(void)
		{
			_data[0] = 0.0f;
			_data[1] = 0.0f;
			_data[2] = 0.0f;
			_data[3] = 0.0f;
		}

		Vector4f::Vector4f(float x, float y, float z, float w)
		{
			_data[0] = x;
			_data[1] = y;
			_data[2] = z;
			_data[3] = w;
		}

		Vector4f::Vector4f(Vector4f const &vec)
		{
			*this = vec;
		}

		Vector4f	&Vector4f::operator=(Vector4f const &rhs)
		{
			_data[0] = rhs._data[0];
			_data[1] = rhs._data[1];
			_data[2] = rhs._data[2];
			_data[3] = rhs._data[3];
			return (*this);
		}

		float		&Vector4f::operator[](int index)
		{
			return (_data[index]);
		}

		float		Vector4f::getX(void)
		{
			return (_data[0]);
		}

		Vector4f	&Vector4f::setX(float v)
		{
			_data[0] = v;
			return (*this);
		}

		float		Vector4f::getY(void)
		{
			return (_data[1]);
		}

		Vector4f	&Vector4f::setY(float v)
		{
			_data[1] = v;
			return (*this);
		}

		float		Vector4f::getZ(void)
		{
			return (_data[2]);
		}

		Vector4f	&Vector4f::setZ(float v)
		{
			_data[2] = v;
			return (*this);
		}

		float		Vector4f::getW(void)
		{
			return (_data[3]);
		}

		Vector4f	&Vector4f::setW(float v)
		{
			_data[3] = v;
			return (*this);
		}

		Vector4f	&Vector4f::set(float x, float y, float z)
		{
			_data[0] = x;
			_data[1] = y;
			_data[2] = z;
			return (*this);
		}

		Vector4f	&Vector4f::set(float x, float y, float z, float w)
		{
			set(x, y, z);
			_data[3] = w;
			return (*this);
		}


		Vector3f	Vector4f::xyz(void)
		{
			return (Vector3f(_data[0], _data[1], _data[2]));
		}
	}
}