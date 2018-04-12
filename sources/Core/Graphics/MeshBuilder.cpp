#include "Core/Graphics/MeshBuilder.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		MeshBuilder::MeshBuilder() :
			vertices(),
			normals(),
			uvs()
		{}

		MeshBuilder::~MeshBuilder()
		{
			vertices.clear();
			normals.clear();
			uvs.clear();
		}

		MeshBuilder		&MeshBuilder::addVertice(glm::vec3 vertice)
		{
			vertices.push_back(vertice);
			return (*this);
		}

		MeshBuilder		&MeshBuilder::addNormal(glm::vec3 normal)
		{
			normals.push_back(normal);
			return (*this);
		}

		MeshBuilder		&MeshBuilder::addUV(glm::vec2 uv)
		{
			uvs.push_back(uv);
			return (*this);
		}

		Mesh			*MeshBuilder::build(void)
		{
			int count = 0;
			if (vertices.size() > 0)
				count++;
			if (normals.size() > 0)
				count++;
			if (uvs.size() > 0)
				count++;
			if (count > 0)
			{
				Mesh	*mesh = new Mesh(count);
				int	i = 0;
				if (vertices.size() > 0)
				{
					mesh->add(i, GL_FLOAT, 3, (void *)(&vertices[0]), vertices.size());
					i++;
				}
				if (normals.size() > 0)
				{
					mesh->add(i, GL_FLOAT, 3, (void *)(&normals[0]), normals.size());
					i++;
				}
				if (uvs.size() > 0)
				{
					mesh->add(i, GL_FLOAT, 2, (void *)(&uvs[0]), uvs.size());
					i++;
				}
				return (mesh);
			}
			return (nullptr);
		}

	}
}