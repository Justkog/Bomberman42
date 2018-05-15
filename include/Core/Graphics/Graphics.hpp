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
			static ShaderProgram	*defaultGuiShader;
			static AMaterial		*defaultMaterial;
			static ALight			*defaultLight;
			static ShaderProgram	*skyboxShader;
			static Cubemap			*defaultCubemap;

			static ShaderProgram	*ambiantShader;
			static ShaderProgram	*directionalShader;
			static ShaderProgram	*spotShader;
			static ShaderProgram	*cubemapShader;
			static ShaderProgram	*shadowRenderShader;
			static ShaderProgram	*shadowShader;

			static void Load(void);
			static void UnLoad(void);

			static void EnableForwardBlend();
			static void DisableForwardBlend();

			static ShaderProgram *loadLineShader();

			static ShaderProgram *loadAmbiantShader();
			static ShaderProgram *loadDirectionalShader();
			static ShaderProgram *loadSpotShader();
			static ShaderProgram *loadSkyboxShader();
			static ShaderProgram *loadCubemapShader();
			static ShaderProgram *loadShadowRenderShader();
			static ShaderProgram *loadShadowShader();

			static Mesh	*OBJLoader(std::string path);
			static Mesh *ModelLoader(std::string path);
		};
	}
}

#endif