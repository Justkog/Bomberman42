#ifndef BE_CORE_GRAPHICS_HPP
#define BE_CORE_GRAPHICS_HPP 1
/*!
 * \file Graphics.hpp
 * \brief Graphics predefini
 * \author mgallo, mploux, jblondea
 */

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
		/*! \class Graphics
		* \brief objet graphique predefini
		*/
		class Graphics
		{
		public:
			static std::map<std::string, Mesh *> typeToMesh; /*!< */
			static Mesh				*plane; /*!< Model de plane predefini*/
			static Mesh				*cube; /*!< Model de cube predefini*/
			static Texture			*whiteTexture; /*!< texture completement blanche*/
			static ShaderProgram	*particleShader; /*!< Shader des particules par defaut*/
			static ShaderProgram	*defaultShader; /*!< Shader par defaut des model*/
			static AMaterial		*defaultMaterial; /*!< Material par defaut*/
			static ShaderProgram	*defaultGuiShader;
			static ALight			*defaultLight;
			static ShaderProgram	*skyboxShader;
			static Cubemap			*defaultCubemap;

			static ShaderProgram	*lightShader;
			static ShaderProgram	*spotShader;
			static ShaderProgram	*cubemapShader;
			static ShaderProgram	*shadowRenderShader;
			static ShaderProgram	*shadowShader;

			/*!
			*  \brief Chargement
			*  Chargement des composents predefini
			*/
			static void Load(void);
			/*!
			*  \brief dechargement
			*  Dechargement des composents predefini
			*/
			static void UnLoad(void);

			static void EnableForwardBlend();
			static void DisableForwardBlend();

			static ShaderProgram *loadLineShader();

			static ShaderProgram *loadLightShader();
			static ShaderProgram *loadSpotShader();
			static ShaderProgram *loadSkyboxShader();
			static ShaderProgram *loadCubemapShader();
			static ShaderProgram *loadShadowRenderShader();
			static ShaderProgram *loadShadowShader();

			static Mesh	* LoadPlane(glm::vec2 tiling, glm::vec2 offset);
			/*!
			*  \brief Chargeur de mdoel
			*  Chargeur de model format obj
			*  \param path : chemin du fichier
			*  \return objet charger
			*/
			static Mesh	*OBJLoader(std::string path);
			static Mesh *ModelLoader(std::string path);
		};
	}
}

#endif