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

		MeshBuilder		&MeshBuilder::addVertice(Maths::Vector3f vertice)
		{
			vertices.push_back(vertice);
			return (*this);
		}

		MeshBuilder		&MeshBuilder::addNormal(Maths::Vector3f normal)
		{
			normals.push_back(normal);
			return (*this);
		}

		MeshBuilder		&MeshBuilder::addUV(Maths::Vector2f uv)
		{
			uvs.push_back(uv);
			return (*this);
		}


		MeshBuilder		&MeshBuilder::addTriangle(Maths::Vector3f v0, Maths::Vector3f v1, Maths::Vector3f v2)
		{
			Maths::Vector3f a = v2 - v0;
			Maths::Vector3f b = v1 - v0;
			Maths::Vector3f normal = a.cross(b).normalize();
			addVertice(v0);
			addVertice(v1);
			addVertice(v2);
			addNormal(normal);
			addNormal(normal);
			addNormal(normal);
			return (*this);
		}

		MeshBuilder		&MeshBuilder::addTriangleUV(Maths::Vector2f uv0, Maths::Vector2f uv1, Maths::Vector2f uv2)
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
				Maths::Vector3f deltaPos1 = vertices[i + 1] - vertices[i];
				Maths::Vector3f deltaPos2 = vertices[i + 2] - vertices[i];
				Maths::Vector3f normal = deltaPos2.cross(deltaPos1).normalize(); //glm::normalize(glm::cross(deltaPos2, deltaPos1));

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
				Maths::Vector3f deltaPos1 = vertices[i + 1] - vertices[i];
				Maths::Vector3f deltaPos2 = vertices[i + 2] - vertices[i];
				// UV delta
				Maths::Vector2f deltaUV1 = uvs[i + 1] - uvs[i];
				Maths::Vector2f deltaUV2 = uvs[i + 2] - uvs[i];
				// Calcul tangent and bitangent
				float r = 1.0f / (deltaUV1.getX() * deltaUV2.getY() - deltaUV1.getY() * deltaUV2.getX());
				Maths::Vector3f tangent = (deltaPos1 * deltaUV2.getY() - deltaPos2 * deltaUV1.getY()) * r;
				Maths::Vector3f bitangent = (deltaPos2 * deltaUV1.getX() - deltaPos1 * deltaUV2.getX()) * r;
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