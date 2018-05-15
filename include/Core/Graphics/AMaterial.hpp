#ifndef BE_CORE_GRAPHICS_AMATERIAL_HPP
#define BE_CORE_GRAPHICS_AMATERIAL_HPP 1
/*!
 * \file AMaterial.hpp
 * \brief Compisition des scenes
 * \author mgallo
 */
#include "Core/Core.hpp"
#include "Core/Json/JsonSerializable.hpp"
/*! \namespace BeerEngine
 * espace de nommage regroupant les fonctionnalité du moteur
 */
#include "Cubemap.hpp"

namespace BeerEngine
{
	/*! \namespace Graphics
	* espace de nommage regroupant les fonctionnalité graphique du moteur
	*/
	namespace Graphics
	{
		/*! \class AMaterial
		* \brief class de material, pour le rendu
		*/
		class AMaterial : public JsonSerializable
		{
		private:
			ShaderProgram	*_shader; /*!< Shader utiliser dans se material*/
			glm::vec4		_color; /*!< Couleur du material*/
			Texture			*_albedo; /*!< Texture afficher sur le material*/
			Texture			*_normal; /*!< Texture Normal utiliser sur la material*/
			Texture			*_bump; /*!< Texture de profondeur utiliser sur le material*/
			Cubemap			*_envMap;

			// Shader ID
			GLint	_colorShaderID; /*!< Identifiant pour bind au shader les divers composents*/
			GLint	_albedoID; /*!< Identifiant pour bind au shader les divers composents*/
			GLint	_hasAlbedoID; /*!< Identifiant pour bind au shader les divers composents*/
			GLint	_normalID; /*!< Identifiant pour bind au shader les divers composents*/
			GLint	_hasNormalID; /*!< Identifiant pour bind au shader les divers composents*/
			GLint	_bumpID; /*!< Identifiant pour bind au shader les divers composents*/
			GLint	_hasBumpID; /*!< Identifiant pour bind au shader les divers composents*/
			GLint	_projectionShaderID; /*!< Identifiant pour bind au shader les divers composents*/
			GLint	_viewShaderID; /*!< Identifiant pour bind au shader les divers composents*/
			GLint	_modelShaderID; /*!< Identifiant pour bind au shader les divers composents*/
			GLint	_viewPosID; /*!< Identifiant pour bind au shader les divers composents*/
			GLint	_viewDirID; /*!< Identifiant pour bind au shader les divers composents*/
			GLint	_envMapID;
			GLint	_hasEnvMapID;

			GLint	_lightPosID;
			GLint	_lightDirID;
			GLint	_lightIntensityID;
			GLint	_lightColorID;
		
		public:
			/*!
			*  \brief Constructeur
			*  Constructeur de la classe AMaterial
			*  \param shader : Shader du material
			*  \param color : couleur par defaut du material
			*/
			AMaterial(ShaderProgram *shader, glm::vec4 color = glm::vec4(1.0f));
			/*!
			*  \brief Destructeur
			*  Destructeur de la classe AMaterial
			*/
			virtual ~AMaterial() {};
			/*!
			*  \brief activer le material
			*  Methode permetant d'activer le material
			*  \param model : matrice de l'objet utilisant se material
			*/
			virtual void	bind(glm::mat4 &model);
			virtual void	bind(glm::mat4 &model, ALight &light);
			/*!
			*  \brief Modifier les parametres de couleur
			*  Methode permetant de modifier les couleur du material
			*  \param color : couleur
			*  \return le material lui même
			*/
			AMaterial		&setColor(glm::vec4 color);
			/*!
			*  \brief Modifier les parametres de texture Albedo
			*  Methode permetant de modifier la texture Albedo du material
			*  \param tex : Texture
			*  \return le material lui même
			*/
			AMaterial		&setAlbedo(Texture *tex);
			/*!
			*  \brief Modifier les parametres de texture de normal
			*  Methode permetant de modifier la normal texture du material
			*  \param tex : Texture
			*  \return le material lui même
			*/
			AMaterial		&setNormal(Texture *tex);
			/*!
			*  \brief Modifier les parametres de la texture de profondeur
			*  Methode permetant de modifier la texture de profondeur du material
			*  \param tex : Texture
			*  \return le material lui même
			*/
			AMaterial		&setBump(Texture *tex);
			AMaterial		&setEnvmap(Cubemap *map);

			ShaderProgram	&getShader();

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader);
			static AMaterial * Deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader);
		};
	}
}

#endif