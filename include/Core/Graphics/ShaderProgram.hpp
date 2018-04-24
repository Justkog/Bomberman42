#ifndef BE_CORE_GRAPHICS_SHADERPROGRAM_HPP
#define BE_CORE_GRAPHICS_SHADERPROGRAM_HPP 1

#include "../Core.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		class ShaderProgram
		{
		private:
			int				_size;
			GLuint			_program;
			GLuint			*_shaders;
		public:
			ShaderProgram(int size);
			~ShaderProgram(void);
			void			load(unsigned int shaderIndex, GLenum shaderType, const char *script);
			void			compile(void);
			void			bind(void);
			void			unbind(void);
			static void		Unbind(void);
			GLint			getUniformLocation(std::string const &name);
			void			uniform1i(std::string const &name, int i);
			void			uniform1i(GLint id, int i);
			void			uniform1f(std::string const &name, float x);
			void			uniform1f(GLint id, float x);
			void			uniform2f(std::string const &name, float x, float y);
			void			uniform2f(GLint id, float x, float y);
			void			uniform2f(std::string const &name, float *data);
			void			uniform2f(std::string const &name, Maths::Vector2f &vec);
			void			uniform3f(std::string const &name, float x, float y, float z);
			void			uniform3f(GLint id, float x, float y, float z);
			void			uniform3f(std::string const &name, Maths::Vector3f &vec);
			void			uniform3f(std::string const &name, float *data);
			void			uniform4f(std::string const &name, float x, float y, float z, float w);
			void			uniform4f(GLint id, float x, float y, float z, float w);
			void			uniform4f(std::string const &name, float *data);
			void			uniformMat(std::string const &name, Maths::Matrix4x4 &mat);
			void			uniformMat(GLint id, Maths::Matrix4x4 &mat);
		};
	}
}

#endif