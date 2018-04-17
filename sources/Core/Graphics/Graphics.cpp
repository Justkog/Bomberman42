#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/MeshBuilder.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		Mesh	*Graphics::plane = nullptr;
		Mesh	*Graphics::cube = nullptr;

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
					glm::vec2(1.0f, 1.0f)
				).addTriangle(
					glm::vec3(1.0f, 0.0f, 1.0f),
					glm::vec3(1.0f, 0.0f, -1.0f),
					glm::vec3(-1.0f, 0.0f, -1.0f)
				).addTriangleUV(
					glm::vec2(1.0f, 1.0f),
					glm::vec2(1.0f, 0.0f),
					glm::vec2(0.0f, 1.0f)
				).calculTangent()
			;
			return (builder.build());
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
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f, -0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// DOWN
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f,  0.5f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// FRONT
				.addVertice(glm::vec3(-0.5f, -0.5f, 0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f, 0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f, 0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// BACK
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f,  -0.5f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  -0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  -0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// LEFT
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f,  0.5f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f, -0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// RIGHT
				.addVertice(glm::vec3(0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3(0.5f, 0.5f, -0.5f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3(0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(0.5f, 0.5f,  0.5f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(0.5f, -0.5f,  0.5f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3(0.5f, -0.5f, -0.5f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// Calcul nornal
				.calculNormal()
				// Calcul Tangent and Bitangent
				.calculTangent()
			;
			return (builder.build());
		}

		void Graphics::Load(void)
		{
			// PLANE
			plane = LoadPlane();
			// CUBE
			cube = LoadCube();
		}

		void Graphics::UnLoad(void)
		{
			delete plane;
			delete cube;
		}
	}
}