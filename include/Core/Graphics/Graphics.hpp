#ifndef BE_CORE_GRAPHICS_HPP
#define BE_CORE_GRAPHICS_HPP 1

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/Core.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "ShaderProgram.hpp"
#include "AMaterial.hpp"

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
			static ShaderProgram	*defaultShader;
			static AMaterial		*defaultMaterial;
			static void Load(void);
			static void UnLoad(void);

			static ShaderProgram *loadLineShader();

			static Mesh	*OBJLoader(std::string path);
			static Mesh *ModelLoader(std::string path);
		};
	}
}

#endif