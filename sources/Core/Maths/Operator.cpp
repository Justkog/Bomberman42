#include "Core/Maths/Maths.hpp"

namespace BeerEngine
{
	namespace Maths
	{
		std::ostream	&operator<<(std::ostream &os, Vector2f &rhs)
		{
			os << "[" << rhs.getX() << ", " << rhs.getY() << "]";
			return (os);
		}

		std::ostream	&operator<<(std::ostream &os, Vector3f &rhs)
		{
			os << "[" << rhs.getX() << ", " << rhs.getY() << ", " << rhs.getZ() << "]";
			return (os);
		}

		std::ostream	&operator<<(std::ostream &os, Vector4f &rhs)
		{
			os << "[" << rhs.getX() << ", " << rhs.getY() << ", " << rhs.getZ() << ", " << rhs.getW() << "]";
			return (os);
		}

		std::ostream	&operator<<(std::ostream &os, Matrix4x4 &rhs)
		{
			os << rhs[0] << " " << rhs[1] << " " << rhs[2] << " " << rhs[3] << std::endl;
			os << rhs[4] << " " << rhs[5] << " " << rhs[6] << " " << rhs[7] << std::endl;
			os << rhs[8] << " " << rhs[9] << " " << rhs[10] << " " << rhs[11] << std::endl;
			os << rhs[12] << " " << rhs[13] << " " << rhs[14] << " " << rhs[15] << std::endl;
			return (os);
		}
	}
}