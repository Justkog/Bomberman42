#ifndef BE_CORE_GRAPHICS_TEXTURE_HPP
#define BE_CORE_GRAPHICS_TEXTURE_HPP 1

#include "../Core.hpp"
#include <png.h>
#include "Core/Json/JsonSerializable.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		class Texture : public JsonSerializable {
		private:
			unsigned int	_width;
			unsigned int	_height;
			unsigned char	*_data;
			GLuint			_textureID;
			std::string		_sourceFile;

		public:
			Texture(unsigned int width, unsigned int height, unsigned char *data, GLenum format = GL_BGR);
			~Texture();
			void	bind(void);
			inline GLuint getID(void) { return (_textureID); }

			static Texture	*LoadBMP(const char *path, GLenum format = GL_BGR);
			static Texture	*LoadPNG(const char *path);
			static Texture	*LoadJPG(const char *path);
			static Texture	*LoadTGA(const char *path);

			int		getWidth(void);
			int		getHeight(void);

			nlohmann::json	serialize();
			static Texture * Deserialize(const nlohmann::json & j);

		};
	}
}

#endif
