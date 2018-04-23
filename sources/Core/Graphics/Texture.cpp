#include "Core/Graphics/Texture.hpp"

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
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_2D, 0);
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
				throw std::logic_error("[Texture BMP] Image could not be opened\n");
			if (fread(header, 1, 54, file) != 54)
				throw std::logic_error("[Texture BMP] Not a correct BMP file\n");
			if (header[0] != 'B' || header[1] != 'M')
				throw std::logic_error("[Texture BMP] Not a correct BMP file\n");
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
			return (new Texture(width, height, data, format));
		}

		Texture		*Texture::LoadPNG(const char *path)
		{
			png_structp png_ptr;
			png_infop info_ptr;
			unsigned int sig_read = 0;
			int color_type, interlace_type;
			FILE *fp;
			if ((fp = fopen(path, "rb")) == NULL)
				throw std::logic_error("[Texture PNG] File could not be opened for reading");
			png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			if (png_ptr == NULL) {
				fclose(fp);
				throw std::logic_error("[Texture PNG] File doesn't valid!");
			}
			info_ptr = png_create_info_struct(png_ptr);
			if (info_ptr == NULL) {
				fclose(fp);
				png_destroy_read_struct(&png_ptr, NULL, NULL);
				throw std::logic_error("[Texture PNG] File doesn't valid!");
			}
			if (setjmp(png_jmpbuf(png_ptr))) {
				png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
				fclose(fp);
				throw std::logic_error("[Texture PNG] File doesn't valid!");
			}
			png_init_io(png_ptr, fp);
			png_set_sig_bytes(png_ptr, sig_read);
			png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
			png_uint_32 width, height;
			int bit_depth;
			png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);
			unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
			unsigned char *outData = new unsigned char[row_bytes * height];
			png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
			for (int i = 0; i < height; i++) {
				std::memcpy(outData + (row_bytes * (height-1-i)), row_pointers[i], row_bytes);
			}
			png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
			fclose(fp);
			return (new Texture(width, height, outData, (color_type == PNG_COLOR_TYPE_RGBA) ? GL_RGBA : GL_RGB));
		}

		int		Texture::getWidth(void)
		{
			return (_width);
		}
		int		Texture::getHeight(void)
		{
			return (_height);
		}
	}
}