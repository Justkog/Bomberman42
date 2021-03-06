#ifndef BE_CORE_GRAPHICS_MESH_HPP
#define BE_CORE_GRAPHICS_MESH_HPP 1
/*!
 * \file Mesh.hpp
 * \brief Classe permettant des rendu graphique
 * \author mgallo
 */
#include "../Core.hpp"
#include "Core/Json/JsonSerializable.hpp"

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
		/*! \class Mesh
		* \brief classe representant les données de rendu
		*/
		class Mesh : public JsonSerializable
		{
		private:
			unsigned int	_nbVBO;
			GLuint			_vao;
			GLuint			*_vbo;
			unsigned int	_size;
			std::string		_sourceFile;
			std::string		_type;

		public:
			Mesh();
			Mesh(const Mesh &val);
			Mesh &operator=(const Mesh &val);

			Mesh(unsigned int nbVBO);
			~Mesh();
			void	add(unsigned int vboIndex, GLenum type, unsigned int width, void *data, unsigned int dataSize, GLenum usage = GL_STATIC_DRAW);
			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader);
			static Mesh * Deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader);
			void setSourcefile(std::string path);
			void setType(std::string type);
			void	render(GLenum mode = GL_TRIANGLES, bool instancing = false, int count = 0, int *divisor = NULL, int divisorCount = 0);
			Mesh	&setSize(unsigned int size);
		};
	}
}

#endif