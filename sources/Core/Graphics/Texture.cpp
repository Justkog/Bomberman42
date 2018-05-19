#include "Core/Graphics/Texture.hpp"
#include "Core/Json/Json.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Game/Assets.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		Texture::Texture(unsigned int width, unsigned int height, unsigned char *data, GLenum format) :
			_width(width), _height(height), _data(data)
		{
			glGenTextures(1, &_textureID);
			glBindTexture(GL_TEXTURE_2D, _textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, format, GL_UNSIGNED_BYTE, _data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1);
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		Texture::Texture()
		{}

		Texture::Texture(const Texture &val)
		{
			*this = val;
		}
		
		Texture &Texture::operator=(const Texture &val)
		{
			if (this != &val)
			{
				Texture::~Texture();
				_width = val._width;
				_height = val._height;
				_data = val._data;
				_textureID = val._textureID;
				_sourceFile = val._sourceFile;
			}
			return (*this);
		}

		Texture::~Texture()
		{
			delete[] _data;
			glDeleteTextures(1, &_textureID);
		}

		void		Texture::bind(void)
		{
			glBindTexture(GL_TEXTURE_2D, _textureID);
		}

		Texture		*Texture::LoadBMP(const char *path, GLenum format)
		{
			unsigned char	header[54];
			unsigned int	dataPos;
			unsigned int	width;
			unsigned int	height;
			unsigned int	imageSize;
			unsigned char	*data;

			FILE *file = fopen(path, "rb");
			if (!file)
				throw std::logic_error(std::string("[Texture BMP] Image could not be opened\n ") + path);
			if (fread(header, 1, 54, file) != 54)
				throw std::logic_error(std::string("[Texture BMP] Not a correct BMP file\n ") + path);
			if (header[0] != 'B' || header[1] != 'M')
				throw std::logic_error(std::string("[Texture BMP] Not a correct BMP file\n ") + path);
			dataPos = *(int*)&(header[0x0A]);
			imageSize = *(int*)&(header[0x22]);
			width = *(int*)&(header[0x12]);
			height = *(int*)&(header[0x16]);
			if (imageSize == 0)
				imageSize = width * height * 3;
			if (dataPos == 0)
				dataPos = 54;
			fseek(file, dataPos, SEEK_SET);
			data = new unsigned char [imageSize];
			fread(data, 1, imageSize, file);
			fclose(file);
			auto texture = new Texture(width, height, data, format);
			texture->_sourceFile = path;
			return (texture);
		}

		Texture		*Texture::LoadPNG(const char *path)
		{

			int	width;
			int	height;
			int	n;
			unsigned char	*data;

			data = stbi_load(path, &width, &height, &n, 4);
			if (!data)
				std::logic_error(std::string("[Texture PNG] File could not be load ") + path);
			auto texture = new Texture(width, height, data, GL_RGBA);
			texture->_sourceFile = path;
			return (texture);
		}

		Texture		*Texture::LoadJPG(const char *path)
		{
			int	width;
			int	height;
			int	n;
			unsigned char	*data;

			data = stbi_load(path, &width, &height, &n, 4);
			if (!data)
				std::logic_error(std::string("[Texture JPG] File could not be load ") + path);
			auto texture = new Texture(width, height, data, GL_RGBA);
			texture->_sourceFile = path;
			return (texture);
		}

		Texture		*Texture::LoadTGA(const char *path)
		{
			int	width;
			int	height;
			int	n;
			unsigned char	*data;

			data = stbi_load(path, &width, &height, &n, 4);
			if (!data)
				std::logic_error(std::string("[Texture JPG] File could not be load ") + path);
			auto texture = new Texture(width, height, data, GL_RGBA);
			texture->_sourceFile = path;
			return (texture);
		}

		int		Texture::getWidth(void)
		{
			return (_width);
		}
		int		Texture::getHeight(void)
		{
			return (_height);
		}

		nlohmann::json	Texture::serialize()
		{
			auto j = JsonSerializable::serialize();
			j.merge_patch({
				{"sourceFile", _sourceFile},
			});
			return j;
		}

		Texture * Texture::Deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			(void) loader;
			if (j.is_null())
				return NULL;
			std::string path = j.at("sourceFile");
			if (path != "")
			{
				// std::cout << "getting texture at " << path << "\n";
				return (Assets::GetTexture(path));
			}
			else
				return NULL;
		}

	}
}
