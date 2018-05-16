#ifndef BE_CORE_GRAPHICS_MESHBUILDER_HPP
#define BE_CORE_GRAPHICS_MESHBUILDER_HPP 1
/*!
 * \file MeshBuilder.hpp
 * \brief Classe permettant de construire un rendu graphique
 * \author mgallo
 */
#include <vector>
#include "../Core.hpp"
#include "Mesh.hpp"
/*! \namespace BeerEngine
 * 
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
	/*! \namespace Graphics
	* espace de nommage regroupant les fonctionnalité graphique du moteur
	*/
	namespace Graphics
	{
		/*! \class MeshBuilder
		* \brief le builder permet de créer des rendu par le biais de mesh, en lui renseignant des vertices ...
		*/
		class MeshBuilder
		{
		private:
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec3> normals;
			std::vector<glm::vec2> uvs;
			std::vector<glm::vec3> tangents;
			std::vector<glm::vec3> bitangents;

		public:
			MeshBuilder();
			~MeshBuilder();
			MeshBuilder		&addVertice(glm::vec3 vertice);
			MeshBuilder		&addNormal(glm::vec3 normal);
			MeshBuilder		&addUV(glm::vec2 uv);
			MeshBuilder		&addTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2);
			MeshBuilder		&addTriangleUV(glm::vec2 uv0, glm::vec2 uv1, glm::vec2 uv2);
			MeshBuilder		&calculNormal(void);
			MeshBuilder		&calculTangent(void);
			MeshBuilder		&clear(void);
			Mesh			*build(void);
		};
	}
}

#endif