#ifndef BE_CORE_GRAPHICS_MESHBUILDER_HPP
#define BE_CORE_GRAPHICS_MESHBUILDER_HPP 1

#include <vector>
#include "../Core.hpp"
#include "Mesh.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		class MeshBuilder
		{
		private:
			std::vector<Maths::Vector3f> vertices;
			std::vector<Maths::Vector3f> normals;
			std::vector<Maths::Vector2f> uvs;
			std::vector<Maths::Vector3f> tangents;
			std::vector<Maths::Vector3f> bitangents;

		public:
			MeshBuilder();
			~MeshBuilder();
			MeshBuilder		&addVertice(Maths::Vector3f vertice);
			MeshBuilder		&addNormal(Maths::Vector3f normal);
			MeshBuilder		&addUV(Maths::Vector2f uv);
			MeshBuilder		&addTriangle(Maths::Vector3f v0, Maths::Vector3f v1, Maths::Vector3f v2);
			MeshBuilder		&addTriangleUV(Maths::Vector2f uv0, Maths::Vector2f uv1, Maths::Vector2f uv2);
			MeshBuilder		&calculNormal(void);
			MeshBuilder		&calculTangent(void);
			MeshBuilder		&clear(void);
			MeshBuilder		&debug(void);
			Mesh			*build(void);
		};
	}
}

#endif