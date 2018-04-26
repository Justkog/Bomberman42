#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/MeshBuilder.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		Mesh	*Graphics::plane = nullptr;
		Mesh	*Graphics::cube = nullptr;
		Texture *Graphics::whiteTexture = nullptr;

		static Mesh	*LoadPlane(void)
		{
			MeshBuilder builder;
			builder.addTriangle(
					Maths::Vector3f(-1.0f, 0.0f, -1.0f),
					Maths::Vector3f(-1.0f, 0.0f, 1.0f),
					Maths::Vector3f(1.0f, 0.0f, 1.0f)
				).addTriangleUV(
					Maths::Vector2f(0.0f, 1.0f),
					Maths::Vector2f(0.0f, 0.0f),
					Maths::Vector2f(1.0f, 0.0f)
				).addTriangle(
					Maths::Vector3f(1.0f, 0.0f, 1.0f),
					Maths::Vector3f(1.0f, 0.0f, -1.0f),
					Maths::Vector3f(-1.0f, 0.0f, -1.0f)
				).addTriangleUV(
					Maths::Vector2f(1.0f, 0.0f),
					Maths::Vector2f(1.0f, 1.0f),
					Maths::Vector2f(0.0f, 1.0f)
				).calculTangent()
			;
			return (builder.build());
		}

		static Mesh	*LoadCube(void)
		{
			MeshBuilder builder;
			builder
				// TOP
				.addVertice(Maths::Vector3f(-0.5f, 0.5f, -0.5f))
				.addUV(Maths::Vector2f(0.0f, 1.0f))
				.addVertice(Maths::Vector3f(-0.5f, 0.5f,  0.5f))
				.addUV(Maths::Vector2f(0.0f, 0.0f))
				.addVertice(Maths::Vector3f( 0.5f, 0.5f,  0.5f))
				.addUV(Maths::Vector2f(1.0f, 0.0f))
				.addVertice(Maths::Vector3f( 0.5f, 0.5f,  0.5f))
				.addUV(Maths::Vector2f(1.0f, 0.0f))
				.addVertice(Maths::Vector3f( 0.5f, 0.5f, -0.5f))
				.addUV(Maths::Vector2f(1.0f, 1.0f))
				.addVertice(Maths::Vector3f(-0.5f, 0.5f, -0.5f))
				.addUV(Maths::Vector2f(0.0f, 1.0f))
				// DOWN
				.addVertice(Maths::Vector3f(-0.5f, -0.5f, -0.5f))
				.addUV(Maths::Vector2f(0.0f, 1.0f))
				.addVertice(Maths::Vector3f( 0.5f, -0.5f, -0.5f))
				.addUV(Maths::Vector2f(0.0f, 0.0f))
				.addVertice(Maths::Vector3f( 0.5f, -0.5f,  0.5f))
				.addUV(Maths::Vector2f(1.0f, 0.0f))
				.addVertice(Maths::Vector3f( 0.5f, -0.5f,  0.5f))
				.addUV(Maths::Vector2f(1.0f, 0.0f))
				.addVertice(Maths::Vector3f(-0.5f, -0.5f,  0.5f))
				.addUV(Maths::Vector2f(1.0f, 1.0f))
				.addVertice(Maths::Vector3f(-0.5f, -0.5f, -0.5f))
				.addUV(Maths::Vector2f(0.0f, 1.0f))
				// FRONT
				.addVertice(Maths::Vector3f(-0.5f, -0.5f, 0.5f))
				.addUV(Maths::Vector2f(0.0f, 1.0f))
				.addVertice(Maths::Vector3f( 0.5f, -0.5f, 0.5f))
				.addUV(Maths::Vector2f(0.0f, 0.0f))
				.addVertice(Maths::Vector3f( 0.5f, 0.5f,  0.5f))
				.addUV(Maths::Vector2f(1.0f, 0.0f))
				.addVertice(Maths::Vector3f( 0.5f, 0.5f,  0.5f))
				.addUV(Maths::Vector2f(1.0f, 0.0f))
				.addVertice(Maths::Vector3f(-0.5f, 0.5f,  0.5f))
				.addUV(Maths::Vector2f(1.0f, 1.0f))
				.addVertice(Maths::Vector3f(-0.5f, -0.5f, 0.5f))
				.addUV(Maths::Vector2f(0.0f, 1.0f))
				// BACK
				.addVertice(Maths::Vector3f(-0.5f, -0.5f, -0.5f))
				.addUV(Maths::Vector2f(0.0f, 1.0f))
				.addVertice(Maths::Vector3f(-0.5f, 0.5f,  -0.5f))
				.addUV(Maths::Vector2f(0.0f, 0.0f))
				.addVertice(Maths::Vector3f( 0.5f, 0.5f,  -0.5f))
				.addUV(Maths::Vector2f(1.0f, 0.0f))
				.addVertice(Maths::Vector3f( 0.5f, 0.5f,  -0.5f))
				.addUV(Maths::Vector2f(1.0f, 0.0f))
				.addVertice(Maths::Vector3f( 0.5f, -0.5f, -0.5f))
				.addUV(Maths::Vector2f(1.0f, 1.0f))
				.addVertice(Maths::Vector3f(-0.5f, -0.5f, -0.5f))
				.addUV(Maths::Vector2f(0.0f, 1.0f))
				// LEFT
				.addVertice(Maths::Vector3f(-0.5f, -0.5f, -0.5f))
				.addUV(Maths::Vector2f(0.0f, 1.0f))
				.addVertice(Maths::Vector3f(-0.5f, -0.5f,  0.5f))
				.addUV(Maths::Vector2f(0.0f, 0.0f))
				.addVertice(Maths::Vector3f(-0.5f, 0.5f,  0.5f))
				.addUV(Maths::Vector2f(1.0f, 0.0f))
				.addVertice(Maths::Vector3f(-0.5f, 0.5f,  0.5f))
				.addUV(Maths::Vector2f(1.0f, 0.0f))
				.addVertice(Maths::Vector3f(-0.5f, 0.5f, -0.5f))
				.addUV(Maths::Vector2f(1.0f, 1.0f))
				.addVertice(Maths::Vector3f(-0.5f, -0.5f, -0.5f))
				.addUV(Maths::Vector2f(0.0f, 1.0f))
				// RIGHT
				.addVertice(Maths::Vector3f(0.5f, -0.5f, -0.5f))
				.addUV(Maths::Vector2f(0.0f, 1.0f))
				.addVertice(Maths::Vector3f(0.5f, 0.5f, -0.5f))
				.addUV(Maths::Vector2f(0.0f, 0.0f))
				.addVertice(Maths::Vector3f(0.5f, 0.5f,  0.5f))
				.addUV(Maths::Vector2f(1.0f, 0.0f))
				.addVertice(Maths::Vector3f(0.5f, 0.5f,  0.5f))
				.addUV(Maths::Vector2f(1.0f, 0.0f))
				.addVertice(Maths::Vector3f(0.5f, -0.5f,  0.5f))
				.addUV(Maths::Vector2f(1.0f, 1.0f))
				.addVertice(Maths::Vector3f(0.5f, -0.5f, -0.5f))
				.addUV(Maths::Vector2f(0.0f, 1.0f))
				// Calcul nornal
				.calculNormal()
				// Calcul Tangent and Bitangent
				.calculTangent()
			;
			builder.debug();
			return (builder.build());
		}

		static Texture	*loadWhiteTexture(void)
		{
			// unsigned char data[] = {255, 255, 255, 255};
			unsigned char *data = new unsigned char[4];
			for (int i = 0; i < 4; i++)
				data[i] = 0xff;
			return (new Texture(1, 1, data, GL_BGRA));
		}

		void Graphics::Load(void)
		{
			// PLANE
			plane = LoadPlane();
			// CUBE
			cube = LoadCube();
			// Texture White
			whiteTexture = loadWhiteTexture();
		}

		void Graphics::UnLoad(void)
		{
			delete plane;
			delete cube;
			delete whiteTexture;
		}
	}
}