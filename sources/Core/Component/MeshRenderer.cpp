#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"
#include "Core/Component/MeshRenderer.hpp"
#include "Core/Graphics/MeshBuilder.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		MeshRenderer::MeshRenderer(GameObject *gameObject) :
			Component(gameObject),
			_mesh(nullptr),
			_material(nullptr)
		{}

		Graphics::Mesh	*MeshRenderer::getMesh(void)
		{
			return (_mesh);
		}

		MeshRenderer		&MeshRenderer::setMesh(Graphics::Mesh *mesh)
		{
			_mesh = mesh;
			return (*this);
		}

		MeshRenderer		&MeshRenderer::setMesh(std::string inputfile)
		{
			tinyobj::attrib_t attrib;
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;

			BeerEngine::Graphics::MeshBuilder builder;

			std::string err;
			bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

			if (!err.empty()) // `err` may contain warning message.
			  std::cerr << err << std::endl;

			if (!ret)
			  exit(1);

			// Loop over shapes
			for (size_t s = 0; s < shapes.size(); s++)
			{
				// Loop over faces(polygon)
				size_t index_offset = 0;

				bool normal = true;
				bool UV = true;

				if (attrib.normals.size() == 0)
					normal = false;
				if (attrib.texcoords.size() == 0)
					UV = false;

				for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
				{
					int fv = shapes[s].mesh.num_face_vertices[f];

					if (normal == false && UV == true)
					{
						for (size_t v = 0; v < fv; v++)
						{
							tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
							// access to vertex
							tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
							tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
							tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
							tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
							tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];

						  builder
							  .addVertice(glm::vec3(vx, vy, vz))
							  .addUV(glm::vec2(tx, ty))
						 ;
						  // Optional: vertex colors
						  // tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
						  // tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
						  // tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
						}
					}
					else if (normal == true && UV == true)
					{
						for (size_t v = 0; v < fv; v++)
						{
							tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
							// access to vertex
							tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
							tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
							tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
							tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
							tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
							tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
							tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
							tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];

							builder
							  .addVertice(glm::vec3(vx, vy, vz))
							  .addNormal(glm::vec3(nx, ny, nz))
							  .addUV(glm::vec2(tx, ty))
						 ;
						  // Optional: vertex colors
						  // tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
						  // tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
						  // tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
						}
					}
					else
					{
						for (size_t v = 0; v < fv; v++)
						{
							tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
							// access to vertex
							tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
							tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
							tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];

						  builder
							  .addVertice(glm::vec3(vx, vy, vz))
						 ;
						  // Optional: vertex colors
						  // tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
						  // tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
						  // tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
						}
					}

					index_offset += fv;
					// per-face material
					shapes[s].mesh.material_ids[f];
				}
			}
			builder.calculTangent();

			return setMesh(builder.build());
		}


		Graphics::AMaterial	*MeshRenderer::getMaterial(void)
		{
			return (_material);
		}

		MeshRenderer	&MeshRenderer::setMaterial(Graphics::AMaterial *material)
		{
			_material = material;
			return (*this);
		}


		void    		MeshRenderer::renderUpdate(void)
		{
			_mat = _gameObject->transform.getMat4();
		}

		void    		MeshRenderer::render(void)
		{
			if (_mesh != nullptr)
			{
				if (_material != nullptr)
					_material->bind(_mat);
				_mesh->render();
			}
		}
	}
}
