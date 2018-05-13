#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/MeshBuilder.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Game/Assets.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		std::map<std::string, Mesh *> Graphics::typeToMesh;
		Mesh			*Graphics::plane = nullptr;
		Mesh			*Graphics::cube = nullptr;
		Texture 		*Graphics::whiteTexture = nullptr;
		ShaderProgram	*Graphics::particleShader = nullptr;
		ShaderProgram	*Graphics::defaultShader = nullptr;
		AMaterial		*Graphics::defaultMaterial = nullptr;

		static Mesh	*LoadPlane(void)
		{
			MeshBuilder builder;
			builder.addTriangle(
					glm::vec3(-1.0f, 0.0f, -1.0f),
					glm::vec3(-1.0f, 0.0f, 1.0f),
					glm::vec3(1.0f, 0.0f, 1.0f)
				).addTriangleUV(
					glm::vec2(0.0f, 1.0f),
					glm::vec2(0.0f, 0.0f),
					glm::vec2(1.0f, 0.0f)
				).addTriangle(
					glm::vec3(1.0f, 0.0f, 1.0f),
					glm::vec3(1.0f, 0.0f, -1.0f),
					glm::vec3(-1.0f, 0.0f, -1.0f)
				).addTriangleUV(
					glm::vec2(1.0f, 0.0f),
					glm::vec2(1.0f, 1.0f),
					glm::vec2(0.0f, 1.0f)
				).calculTangent()
			;
			auto plane = builder.build();
			plane->setType("plane");
			Graphics::typeToMesh["plane"] = plane;
			return (plane);
		}

		static Mesh	*LoadCube(void)
		{
			MeshBuilder builder;
			builder
				// TOP
				.addVertice(glm::vec3(-0.5f, 0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f, -0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// DOWN
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// FRONT
				.addVertice(glm::vec3(-0.5f, -0.5f, 0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f, 0.5f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f, 0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// BACK
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f,  -0.5f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  -0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  -0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// LEFT
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f,  0.5f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f, -0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// RIGHT
				.addVertice(glm::vec3(0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3(0.5f, 0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3(0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3(0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3(0.5f, -0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// Calcul nornal
				.calculNormal()
				// Calcul Tangent and Bitangent
				.calculTangent()
			;
			auto cube = builder.build();
			cube->setType("cube");
			Graphics::typeToMesh["cube"] = cube;
			return (cube);
		}

		static Texture	*loadWhiteTexture(void)
		{
			// unsigned char data[] = {255, 255, 255, 255};
			unsigned char *data = new unsigned char[4];
			for (int i = 0; i < 4; i++)
				data[i] = 0xff;
			return (new Texture(1, 1, data, GL_BGRA));
		}

		static ShaderProgram *loadParticleShader(void)
		{
			// ShaderProgram *shader = new BeerEngine::Graphics::ShaderProgram(2);
			// shader->load(0, GL_VERTEX_SHADER,
			// 	BeerEngine::IO::FileUtils::LoadFile("shaders/particle_v.glsl").c_str()
			// );
			// shader->load(1, GL_FRAGMENT_SHADER,
			// 	BeerEngine::IO::FileUtils::LoadFile("shaders/particle_f.glsl").c_str()
			// );
			// // shader->load(2, GL_GEOMETRY_SHADER,
			// // 	BeerEngine::IO::FileUtils::LoadFile("shaders/particle_g.glsl").c_str()
			// // );
			// shader->compile();
			return (Assets::GetShaderProgram("shaders/particle_v.glsl", "shaders/particle_f.glsl"));
		}

		ShaderProgram *Graphics::loadLineShader(void)
		{
			// ShaderProgram *shader = new BeerEngine::Graphics::ShaderProgram(2);
			// shader->load(0, GL_VERTEX_SHADER,
			// 	BeerEngine::IO::FileUtils::LoadFile("shaders/line_v.glsl").c_str()
			// );
			// shader->load(1, GL_FRAGMENT_SHADER,
			// 	BeerEngine::IO::FileUtils::LoadFile("shaders/line_f.glsl").c_str()
			// );
			// shader->compile();
			return (Assets::GetShaderProgram("shaders/line_v.glsl", "shaders/line_f.glsl"));
		}

		void Graphics::Load(void)
		{
			// PLANE
			plane = LoadPlane();
			// CUBE
			cube = LoadCube();
			// Texture White
			whiteTexture = loadWhiteTexture();
			//Shader Particle;
			particleShader = loadParticleShader();
			defaultShader = Assets::GetShaderProgram("shaders/basic_v.glsl", "shaders/basic_f.glsl");
			defaultMaterial = new AMaterial(defaultShader);
		}

		void Graphics::UnLoad(void)
		{
			delete plane;
			delete cube;
			delete whiteTexture;
			delete particleShader;
			delete defaultShader;
			delete defaultMaterial;
		}

		Mesh	*Graphics::OBJLoader(std::string path)
		{
			tinyobj::attrib_t attrib;
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;

			BeerEngine::Graphics::MeshBuilder builder;

			std::string err;
			bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str());

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
			if (attrib.texcoords.size() > 0)
				builder.calculTangent();
			auto mesh = builder.build();
			mesh->setSourcefile(path);
			return (mesh);
		}
	}
}