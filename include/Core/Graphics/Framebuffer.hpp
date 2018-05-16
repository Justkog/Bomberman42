#ifndef BE_CORE_GRAPHICS_FRAMEBUFFER_HPP
#define BE_CORE_GRAPHICS_FRAMEBUFFER_HPP 1

#include "../Core.hpp"
#include <png.h>
#include "Core/Json/JsonSerializable.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		class Framebuffer : public JsonSerializable {
		private:
			unsigned int	_width;
			unsigned int	_height;
			
			GLuint			_fboID;
			GLuint			_depthID;
			GLuint			_textureID;
			GLuint			_depthTextureID;

			void	createColorTextureAttachement();
			void	createDepthTextureAttachement();
			void	createDepthBufferAttachement();

		public:
			Framebuffer(unsigned int width, unsigned int height);
			~Framebuffer();
			
			void	bind(void);
			void	bindDepth(void);
			void	unbind(void);
			
			GLuint getTextureID(void);
			GLuint getDepthTextureID(void);
			GLuint getID(void);
			GLuint getDepthID(void);

			int		getWidth(void);
			int		getHeight(void);

			nlohmann::json	serialize();
			static Framebuffer * Deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader);

		};
	}
}

#endif
