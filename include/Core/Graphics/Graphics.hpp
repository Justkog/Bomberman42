#ifndef BE_CORE_GRAPHICS_HPP
#define BE_CORE_GRAPHICS_HPP 1

#include "../Core.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		class Graphics
		{
		public:
			static Mesh		*plane;
			static Mesh		*cube;
			static Texture	*whiteTexture;
			static void Load(void);
			static void UnLoad(void);
		};
	}
}

#endif