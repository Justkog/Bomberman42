#include "Core/Graphics/MeshBuilder.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		MeshBuilder::MeshBuilder() :
			vertices(),
			normals(),
			uvs(),
			tangents(),
			bitangents()
		{}

		MeshBuilder::~MeshBuilder()
		{
			clear();
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


		MeshBuilder		&MeshBuilder::addTriangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
		{
			glm::vec3 normal = glm::normalize(glm::cross(v2 - v0, v1 - v0));
			addVertice(v0);
			addVertice(v1);
			addVertice(v2);
			addNormal(normal);
			addNormal(normal);
			addNormal(normal);
			return (*this);
		}

		MeshBuilder		&MeshBuilder::addTriangleUV(glm::vec2 uv0, glm::vec2 uv1, glm::vec2 uv2)
		{
			addUV(uv0);
			addUV(uv1);
			addUV(uv2);
			return (*this);
		}

		MeshBuilder		&MeshBuilder::calculNormal(void)
		{
			for (int i = 0; i < vertices.size(); i+=3)
			{
				glm::vec3 deltaPos1 = vertices[i + 1] - vertices[i];
				glm::vec3 deltaPos2 = vertices[i + 2] - vertices[i];
				glm::vec3 normal = glm::normalize(glm::cross(deltaPos2, deltaPos1));

				addNormal(normal);
				addNormal(normal);
				addNormal(normal);
			}
			return (*this);
		}

		MeshBuilder		&MeshBuilder::calculTangent(void)
		{
			for (int i = 0; i < vertices.size(); i+=3)
			{
				// Edges of the triangle : postion delta
				glm::vec3 deltaPos1 = vertices[i + 1] - vertices[i];
				glm::vec3 deltaPos2 = vertices[i + 2] - vertices[i];
				// UV delta
				glm::vec2 deltaUV1 = uvs[i + 1] - uvs[i];
				glm::vec2 deltaUV2 = uvs[i + 2] - uvs[i];
				// Calcul tangent and bitangent
				float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
				glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
				glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;
				// Add to list
				tangents.push_back(tangent);
				tangents.push_back(tangent);
				tangents.push_back(tangent);
				bitangents.push_back(bitangent);
				bitangents.push_back(bitangent);
				bitangents.push_back(bitangent);
			}
			return (*this);
		}

		MeshBuilder		&MeshBuilder::clear(void)
		{
			vertices.clear();
			normals.clear();
			uvs.clear();
			tangents.clear();
			bitangents.clear();
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
			if (tangents.size() > 0)
				count++;
			if (bitangents.size() > 0)
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
				if (tangents.size() > 0)
				{
					mesh->add(i, GL_FLOAT, 3, (void *)(&tangents[0]), tangents.size());
					i++;
				}
				if (bitangents.size() > 0)
				{
					mesh->add(i, GL_FLOAT, 3, (void *)(&bitangents[0]), bitangents.size());
					i++;
				}
				return (mesh);
			}
			return (nullptr);
		}

	}
}