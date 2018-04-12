#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/MeshBuilder.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		Mesh	*Graphics::plane = nullptr;
		Mesh	*Graphics::cube = nullptr;

		static void	LoadPlane(Mesh *plane)
		{
			const glm::vec3 vectices[] = {
				glm::vec3(-1.0f, 0.0f, -1.0f),
				glm::vec3(-1.0f, 0.0f, 1.0f),
				glm::vec3(1.0f, 0.0f, 1.0f),
				glm::vec3(1.0f, 0.0f, 1.0f),
				glm::vec3(1.0f, 0.0f, -1.0f),
				glm::vec3(-1.0f, 0.0f, -1.0f)
			};
			plane->add(0, GL_FLOAT, 3, (void *)vectices, 6);
			const glm::vec3 normals[] = {
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f)
			};
			plane->add(1, GL_FLOAT, 3, (void *)normals, 6);
			const glm::vec2 uvs[] = {
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(0.0f, 1.0f)
			};
			plane->add(2, GL_FLOAT, 2, (void *)uvs, 6);
		}

		static Mesh	*LoadCube(void)
		{
			MeshBuilder builder;
			builder
				// TOP
				.addVertice(glm::vec3(-0.5f, 0.5f, -0.5f))
				.addNormal(glm::vec3(0.0f, 1.0f, 0.0f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f,  0.5f))
				.addNormal(glm::vec3(0.0f, 1.0f, 0.0f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  0.5f))
				.addNormal(glm::vec3(0.0f, 1.0f, 0.0f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  0.5f))
				.addNormal(glm::vec3(0.0f, 1.0f, 0.0f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f, -0.5f))
				.addNormal(glm::vec3(0.0f, 1.0f, 0.0f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f, -0.5f))
				.addNormal(glm::vec3(0.0f, 1.0f, 0.0f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// DOWN
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addNormal(glm::vec3(0.0f, -1.0f, 0.0f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f, -0.5f))
				.addNormal(glm::vec3(0.0f, -1.0f, 0.0f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f,  0.5f))
				.addNormal(glm::vec3(0.0f, -1.0f, 0.0f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f,  0.5f))
				.addNormal(glm::vec3(0.0f, -1.0f, 0.0f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f,  0.5f))
				.addNormal(glm::vec3(0.0f, -1.0f, 0.0f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addNormal(glm::vec3(0.0f, -1.0f, 0.0f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// FRONT
				.addVertice(glm::vec3(-0.5f, -0.5f, 0.5f))
				.addNormal(glm::vec3(0.0f, 0.0f, 1.0f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f, 0.5f))
				.addNormal(glm::vec3(0.0f, 0.0f, 1.0f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  0.5f))
				.addNormal(glm::vec3(0.0f, 0.0f, 1.0f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  0.5f))
				.addNormal(glm::vec3(0.0f, 0.0f, 1.0f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f,  0.5f))
				.addNormal(glm::vec3(0.0f, 0.0f, 1.0f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f, 0.5f))
				.addNormal(glm::vec3(0.0f, 0.0f, 1.0f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// BACK
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addNormal(glm::vec3(0.0f, 0.0f, -1.0f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f,  -0.5f))
				.addNormal(glm::vec3(0.0f, 0.0f, -1.0f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  -0.5f))
				.addNormal(glm::vec3(0.0f, 0.0f, -1.0f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, 0.5f,  -0.5f))
				.addNormal(glm::vec3(0.0f, 0.0f, -1.0f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3( 0.5f, -0.5f, -0.5f))
				.addNormal(glm::vec3(0.0f, 0.0f, -1.0f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addNormal(glm::vec3(0.0f, 0.0f, -1.0f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// LEFT
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addNormal(glm::vec3(-1.0f, 0.0f, 0.0f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f,  0.5f))
				.addNormal(glm::vec3(-1.0f, 0.0f, 0.0f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f,  0.5f))
				.addNormal(glm::vec3(-1.0f, 0.0f, 0.0f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f,  0.5f))
				.addNormal(glm::vec3(-1.0f, 0.0f, 0.0f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(-0.5f, 0.5f, -0.5f))
				.addNormal(glm::vec3(-1.0f, 0.0f, 0.0f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3(-0.5f, -0.5f, -0.5f))
				.addNormal(glm::vec3(-1.0f, 0.0f, 0.0f))
				.addUV(glm::vec2(0.0f, 1.0f))
				// RIGHT
				.addVertice(glm::vec3(0.5f, -0.5f, -0.5f))
				.addNormal(glm::vec3(1.0f, 0.0f, 0.0f))
				.addUV(glm::vec2(0.0f, 1.0f))
				.addVertice(glm::vec3(0.5f, 0.5f, -0.5f))
				.addNormal(glm::vec3(1.0f, 0.0f, 0.0f))
				.addUV(glm::vec2(1.0f, 0.0f))
				.addVertice(glm::vec3(0.5f, 0.5f,  0.5f))
				.addNormal(glm::vec3(1.0f, 0.0f, 0.0f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(0.5f, 0.5f,  0.5f))
				.addNormal(glm::vec3(1.0f, 0.0f, 0.0f))
				.addUV(glm::vec2(1.0f, 1.0f))
				.addVertice(glm::vec3(0.5f, -0.5f,  0.5f))
				.addNormal(glm::vec3(1.0f, 0.0f, 0.0f))
				.addUV(glm::vec2(0.0f, 0.0f))
				.addVertice(glm::vec3(0.5f, -0.5f, -0.5f))
				.addNormal(glm::vec3(1.0f, 0.0f, 0.0f))
				.addUV(glm::vec2(0.0f, 1.0f))
			;
			return (builder.build());
		}

		void Graphics::Load(void)
		{
			// PLANE
			plane = new Mesh(3);
			LoadPlane(plane);
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