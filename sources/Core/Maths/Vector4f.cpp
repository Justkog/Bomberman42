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

	}
}