//
// Created by mploux on 12/05/18.
//

#ifndef BE_CORE_GRAPHICS_CUBEMAP_HPP
#define BE_CORE_GRAPHICS_CUBEMAP_HPP 1
/*!
 * \file Cubemap.hpp
 * \brief Le Cube Mapping permet de simuler la réflexion d'un environnement sur un objet
 * \author mploux
 */
#include <Core/Component/IRender.hpp>
#include "ShaderProgram.hpp"
#include "Texture.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		/*! \class Cubemap
		* \brief classe permettant de regrouper les donner de la cubemap pour la simuler la réflexion d'un environnement sur les objets
		*/
		class Cubemap : public JsonSerializable, public Component::IRender
		{
		private:
			ShaderProgram	*_shader;
			Texture			*_envMap;

			GLuint			_cubeMapID;

			Mesh			*_cube;

			void generateMipmaps(int size, glm::mat4 views[6]);

		public:
			Cubemap();
			Cubemap(const Cubemap &val);
			Cubemap &operator=(const Cubemap &val);

			Cubemap(const std::string &paths, int size);
			virtual ~Cubemap() {};

			void    renderUpdate(void);
			void    render(void);

			void	bind();
			void	unbind();

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);
			static Cubemap * Deserialize(const nlohmann::json & j);
		};
	}
}

#endif
