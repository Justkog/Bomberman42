#include "Core/Graphics/Mesh.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Game/Assets.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		Mesh::Mesh(unsigned int nbVBO) :
			_nbVBO(nbVBO),
			_vao(0),
			_vbo(NULL),
			_size(0)
		{
			glGenVertexArrays(1, &(_vao));
			if (_nbVBO > 0 && _vao)
			{
				glBindVertexArray(_vao);
				_vbo = new GLuint[_nbVBO];
				glGenBuffers(_nbVBO, _vbo);
				glBindVertexArray(0);
			}
		}

		Mesh::Mesh()
		{}

		Mesh::Mesh(const Mesh &val)
		{
			*this = val;
		}
		
		Mesh &Mesh::operator=(const Mesh &val)
		{
			if (this != &val)
			{
				Mesh::~Mesh();
				_nbVBO = val._nbVBO;
				_vao = val._vao;
				_vbo = val._vbo;
				_size = val._size;
				_sourceFile = val._sourceFile;
				_type = val._type;
			}
			return (*this);
		}

		Mesh::~Mesh()
		{
			if (_nbVBO > 0)
			{
				glDeleteBuffers(_nbVBO, _vbo);
				delete[] _vbo;
			}
			if (_vao)
				glDeleteVertexArrays(1, &_vao);
		}
		void			Mesh::add(unsigned int vboIndex, GLenum type, unsigned int width, void *data, unsigned int dataSize, GLenum usage)
		{
			unsigned int s;
			if (!_vao || vboIndex >= _nbVBO || !_vbo[vboIndex])
				return ;
			if (type == GL_FLOAT)
				s = sizeof(GLfloat);
			else if (type == GL_INT)
				s = sizeof(GLint);
			else if (type == GL_BYTE)
				s = sizeof(GLbyte);
			else if (type == GL_UNSIGNED_BYTE)
				s = sizeof(GLubyte);
			else if (type == GL_SHORT)
				s = sizeof(GLshort);
			else if (type == GL_UNSIGNED_SHORT)
				s = sizeof(GLushort);
			else if (type == GL_UNSIGNED_INT)
				s = sizeof(GLuint);
			else if (type == GL_DOUBLE)
				s = sizeof(GLdouble);
			else
				s = sizeof(GLfloat);
			_size = dataSize;
			glBindVertexArray(_vao);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo[vboIndex]);
			glBufferData(GL_ARRAY_BUFFER, s * width * dataSize, data, usage);
			if (type == GL_INT || type == GL_UNSIGNED_INT || type == GL_BYTE
				|| type == GL_UNSIGNED_BYTE || type == GL_SHORT || type == GL_UNSIGNED_SHORT)
				glVertexAttribIPointer(vboIndex, width, type, 0, (void *)0);
			else
				glVertexAttribPointer(vboIndex, width, type, GL_FALSE, 0, (void *)0);
			glEnableVertexAttribArray(vboIndex);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void			Mesh::render(GLenum mode, bool instancing, int count, int *divisor, int divisorCount)
		{
			glBindVertexArray(_vao);
			if (instancing)
			{
				if (count > 0)
				{
					for (int i = 0; i < divisorCount; i++)
						glVertexAttribDivisor(i, divisor[i]);
					glDrawArraysInstanced(mode, 0, _size, count);
				}
			}
			else
				glDrawArrays(mode, 0, _size);
			glBindVertexArray(0);
		}

		nlohmann::json	Mesh::serialize()
		{
			auto j = JsonSerializable::serialize();
			j.merge_patch({
				{"sourceFile", _sourceFile},
				{"type", _type},
			});
			return j;
		}

		void Mesh::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			this->JsonSerializable::deserialize(j, loader);
		}

		Mesh *Mesh::Deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			(void) loader;
			if (j.is_null())
				return NULL;
			std::string path = j.at("sourceFile");
			if (path != "")
				return (Assets::GetModel(path));
			std::string type = j.at("type");
			if (type != "")
				return (NULL);
			else
				return NULL;
		}

		void Mesh::setSourcefile(std::string path)
		{
			_sourceFile = path;
		}

		void Mesh::setType(std::string type)
		{
			_type = type;
		}
		
		Mesh	&Mesh::setSize(unsigned int size)
		{
			_size = size;
			return (*this);
		}
	}
}
