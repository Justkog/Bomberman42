#include "Core/Graphics/Graphics.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		Mesh	*Graphics::plane = nullptr;

		void Graphics::Load(void)
		{
			plane = new Mesh(3);
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

		void Graphics::UnLoad(void)
		{
			delete plane;
		}
	}
}