#ifndef BE_CORE_GRAPHICS_MESH_HPP
#define BE_CORE_GRAPHICS_MESH_HPP 1

#include "../Core.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		class Mesh
		{
		private:
			unsigned int	_nbVBO;
			GLuint			_vao;
			GLuint			*_vbo;
			unsigned int	_size;
		public:
			Mesh(unsigned int nbVBO);
			~Mesh();
			void	add(unsigned int vboIndex, GLenum type, unsigned int width, void *data, unsigned int dataSize, GLenum usage = GL_STATIC_DRAW);
			void	render(GLenum mode = GL_TRIANGLES, bool instancing = false, int count = 0, int *divisor = NULL, int divisorCount = 0);
			Mesh	&setSize(unsigned int size);
		};
	}
}

#endif