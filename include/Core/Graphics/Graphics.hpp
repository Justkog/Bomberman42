#ifndef BE_CORE_GRAPHICS_HPP
#define BE_CORE_GRAPHICS_HPP 1

#include "Core/Core.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "ShaderProgram.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		class Graphics
		{
		public:
			static std::map<std::string, Mesh *> typeToMesh;
			static Mesh				*plane;
			static Mesh				*cube;
			static Texture			*whiteTexture;
			static ShaderProgram	*particleShader;

			static void Load(void);
			static void UnLoad(void);

			static Mesh	*OBJLoader(std::string path);
		};
	}
}

#endif