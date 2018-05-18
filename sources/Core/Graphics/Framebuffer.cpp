#include "Core/Graphics/Framebuffer.hpp"
#include "Core/Json/Json.hpp"
#include "Game/Assets.hpp"
#include "Core/Window.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		Framebuffer::Framebuffer(unsigned int width, unsigned int height)
			: _width(width), _height(height)
		{
			glGenFramebuffers(1, &_fboID);
			glBindFramebuffer(GL_FRAMEBUFFER, _fboID);
			glDrawBuffer(GL_COLOR_ATTACHMENT0);
			
			createColorTextureAttachement();
			createDepthTextureAttachement();
			createDepthBufferAttachement();
			
			unbind();
		}

		Framebuffer::~Framebuffer()
		{
			glDeleteFramebuffers(1, &_fboID);
			glDeleteFramebuffers(1, &_depthID);
			glDeleteTextures(1, &_textureID);
			glDeleteTextures(1, &_depthTextureID);
		}
		
		void Framebuffer::createColorTextureAttachement()
		{
			glGenTextures(1, &_textureID);
			glBindTexture(GL_TEXTURE_2D, _textureID);
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureID, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		
		void Framebuffer::createDepthTextureAttachement()
		{
			glGenTextures(1, &_depthTextureID);
			glBindTexture(GL_TEXTURE_2D, _depthTextureID);
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, _width, _height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthTextureID, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		
		void Framebuffer::createDepthBufferAttachement()
		{
			glGenRenderbuffers(1, &_depthID);
			glBindRenderbuffer(GL_RENDERBUFFER, _depthID);

			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthID);
		}

		void	Framebuffer::bind(void)
		{
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fboID);
			glViewport(0, 0, _width, _height);
		}

		void	Framebuffer::bindDepth()
		{
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _depthID);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthTextureID, 0);
			glViewport(0, 0, _width, _height);
		}

		void	Framebuffer::unbind(void)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, Window::GetInstance()->getWidth(), Window::GetInstance()->getHeight());
		}
		
		GLuint Framebuffer::getTextureID(void)
		{
			return (_textureID);
		}
		
		GLuint Framebuffer::getDepthTextureID(void)
		{
			return (_depthTextureID);
		}
		
		GLuint Framebuffer::getID(void)
		{
			return (_fboID);
		}
		
		GLuint Framebuffer::getDepthID(void)
		{
			return (_depthID);
		}

		int		Framebuffer::getWidth(void)
		{
			return (_width);
		}

		int		Framebuffer::getHeight(void)
		{
			return (_height);
		}

		nlohmann::json	Framebuffer::serialize()
		{

		}

		Framebuffer * Framebuffer::Deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{

		}
	}
}
