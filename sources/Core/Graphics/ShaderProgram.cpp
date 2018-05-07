#include "Core/Graphics/ShaderProgram.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		ShaderProgram::ShaderProgram(int size) :
			_size(size),
			_program(0),
			_shaders(NULL)
		{
			if (_size > 0)
			{
				_shaders = new GLuint[_size];
				for (unsigned int i = 0; i < _size; i++)
					_shaders[i] = 0;
			}
		}

		ShaderProgram::~ShaderProgram()
		{
			if (_shaders != NULL)
			{
				for (unsigned int i = 0; i < _size; i++)
				{
					if (_shaders[i])
					{
						glDetachShader(_program, _shaders[i]);
						glDeleteShader(_shaders[i]);
						_shaders[i] = 0;
					}
				}
				delete[] _shaders;
			}
			if (_program)
				glDeleteProgram(_program);
		}

		void			ShaderProgram::load(unsigned int shaderIndex, GLenum shaderType, const char *script)
		{
			if (shaderIndex >= _size)
				return ;
			_shaders[shaderIndex] = glCreateShader(shaderType);
			glShaderSource(_shaders[shaderIndex], 1, (const GLchar *const *)&script, NULL);
			glCompileShader(_shaders[shaderIndex]);
			// TEST DEBUG
			GLint	result;
			glGetShaderiv(_shaders[shaderIndex], GL_COMPILE_STATUS, &result);
			if (result == 0)
			{
				int		log_length;
				glGetShaderiv(_shaders[shaderIndex], GL_INFO_LOG_LENGTH, &log_length);
				if (!log_length)
					return ;
				char	*log = new char[log_length];
				glGetShaderInfoLog(_shaders[shaderIndex], log_length, NULL, log);
				if (shaderType == GL_VERTEX_SHADER)
					std::cout << "Vertex Shader:" << std::endl;
				else if (shaderType == GL_FRAGMENT_SHADER)
					std::cout << "Fragment Shader:" << std::endl;
				else if (shaderType == GL_GEOMETRY_SHADER)
					std::cout << "Geometry Shader:" << std::endl;
				else
					std::cout << "Other Shader:" << std::endl;
				std::cout << log;
				delete[] log;
			}
		}

		void			ShaderProgram::compile(void)
		{
			_program = glCreateProgram();
			if (!_program)
				return ;
			for (unsigned int i = 0; i < _size; i++)
			{
				if (_shaders[i])
					glAttachShader(_program, _shaders[i]);
			}
			glLinkProgram(_program);
			// TEST DEBUG
			GLint	result;
			glGetProgramiv(_program, GL_LINK_STATUS, &result);
			if (result == 0)
			{
				int log_length;
				glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &log_length);
				if (log_length)
				{
					char	*log = new char[log_length];
					glGetProgramInfoLog(_program, log_length, NULL, log);
					std::cout << log;
					delete[] log;
				}
			}
			// DELETE LAST
			for (unsigned int i = 0; i < _size; i++)
			{
				if (_shaders[i])
				{
					glDetachShader(_program, _shaders[i]);
					glDeleteShader(_shaders[i]);
					_shaders[i] = 0;
				}
			}
		}

		void			ShaderProgram::bind(void)
		{
			glUseProgram(_program);
		}

		void			ShaderProgram::unbind(void)
		{
			ShaderProgram::Unbind();
		}

		void			ShaderProgram::Unbind(void)
		{
			glUseProgram(0);
		}

		GLint			ShaderProgram::getUniformLocation(std::string const &name)
		{
			return (glGetUniformLocation(_program, name.c_str()));
		}

		void			ShaderProgram::uniform1i(std::string const &name, int i)
		{
			GLint id = glGetUniformLocation(_program, name.c_str());
			uniform1i(id, i);
		}

		void			ShaderProgram::uniform1i(GLint id, int i)
		{
			glUniform1i(id, i);
		}

		void			ShaderProgram::uniform1f(std::string const &name, float x)
		{
			GLint id = glGetUniformLocation(_program, name.c_str());
			uniform1f(id, x);
		}

		void			ShaderProgram::uniform1f(GLint id, float x)
		{
			glUniform1f(id, x);
		}

		void			ShaderProgram::uniform2f(std::string const &name, float x, float y)
		{
			GLint id = glGetUniformLocation(_program, name.c_str());
			uniform2f(id, x, y);
		}

		void			ShaderProgram::uniform2f(GLint id, float x, float y)
		{
			glUniform2f(id, x, y);
		}

		void			ShaderProgram::uniform2f(std::string const &name, float *data)
		{
			uniform2f(name, data[0], data[1]);
		}

		void			ShaderProgram::uniform2f(std::string const &name, glm::vec2 const &vec)
		{
			uniform2f(name, vec[0], vec[1]);
		}

		void			ShaderProgram::uniform3f(std::string const &name, float x, float y, float z)
		{
			GLint id = glGetUniformLocation(_program, name.c_str());
			uniform3f(id, x, y, z);
		}

		void			ShaderProgram::uniform3f(GLint id, float x, float y, float z)
		{
			glUniform3f(id, x, y, z);
		}

		void			ShaderProgram::uniform3f(std::string const &name, glm::vec3 const &vec)
		{
			uniform3f(name, vec[0], vec[1],vec[2]);
		}

		void			ShaderProgram::uniform3f(std::string const &name, float *data)
		{
			uniform3f(name, data[0], data[1], data[2]);
		}

		void			ShaderProgram::uniform4f(std::string const &name, glm::vec4 const &vec)
		{
			uniform4f(name, vec[0], vec[1], vec[2], vec[3]);
		}

		void			ShaderProgram::uniform4f(std::string const &name, float x, float y, float z, float w)
		{
			GLint id = glGetUniformLocation(_program, name.c_str());
			uniform4f(id, x, y, z, w);
		}

		void			ShaderProgram::uniform4f(GLint id, float x, float y, float z, float w)
		{
			glUniform4f(id, x, y, z, w);
		}

		void			ShaderProgram::uniform4f(std::string const &name, float *data)
		{
			uniform4f(name, data[0], data[1], data[2], data[3]);
		}

		void			ShaderProgram::uniformMat(std::string const &name, glm::mat4 &mat)
		{
			// std::cout << name << std::endl;
			GLint id = glGetUniformLocation(_program, name.c_str());
			uniformMat(id, mat);
		}

		void			ShaderProgram::uniformMat(GLint id, glm::mat4 &mat)
		{
			glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(mat));
		}
	}
}