#ifndef BE_CORE_GRAPHICS_HPP
#define BE_CORE_GRAPHICS_HPP 1
/*!
 * \file Graphics.hpp
 * \brief Graphics predefini
 * \author mgallo
 */
#include "Core/Core.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "ShaderProgram.hpp"
#include "AMaterial.hpp"
/*! \namespace BeerEngine
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
	/*! \namespace Graphics
	* espace de nommage regroupant les fonctionnalité graphique du moteur
	*/
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

			static ShaderProgram *loadLineShader();
			/*!
			*  \brief Chargeur de mdoel
			*  Chargeur de model format obj
			*  \param path : chemin du fichier
			*  \return objet charger
			*/
			static Mesh	*OBJLoader(std::string path);
		};
	}
}

#endif