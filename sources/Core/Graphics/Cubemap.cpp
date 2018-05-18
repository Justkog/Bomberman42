//
// Created by mploux on 12/05/18.
//

#include <Core/Graphics/Graphics.hpp>
#include <Game/Assets.hpp>
#include <Core/Window.hpp>
#include <Core/Camera.hpp>
#include <Core/IO/FileUtils.hpp>
#include "Core/Graphics/Cubemap.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		Cubemap::Cubemap(const std::string &path, int size)
		{
			glm::mat4 views[6] =
			{
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
				glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
			};

			_shader = Graphics::Graphics::skyboxShader;
			_envMap = Assets::GetTexture(path);
			glDisable(GL_CULL_FACE);
			generateMipmaps(size, views);
			glEnable(GL_CULL_FACE);
		}

		Cubemap::Cubemap()
		{}

		Cubemap::Cubemap(const Cubemap &val)
		{
			*this = val;
		}
		
		Cubemap &Cubemap::operator=(const Cubemap &val)
		{
			if (this != &val)
			{

			}
			return (*this);
		}

		void	Cubemap::generateMipmaps(int size, glm::mat4 views[6])
		{
			ShaderProgram *shader = Graphics::cubemapShader;

			GLuint fbo;
			GLuint rbo;

			glGenTextures(1, &_cubeMapID);
			glGenFramebuffers(1, &fbo);
			glGenRenderbuffers(1, &rbo);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeMapID);
			for (unsigned int i = 0; i < 6; ++i)
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, size, size, 0, GL_RGB, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
			shader->bind();

			glActiveTexture(GL_TEXTURE0);
			shader->uniform1i("env_map", 0);
			_envMap->bind();

			glm::mat4 persp = glm::perspective(glm::radians(90.0), 1.0, 0.1, 2.0);
			shader->uniformMat("projection", persp);

			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			for (int mip = 0; mip < 5; mip++)
			{
				int mip_size = size * std::pow(0.5, mip);
				GLfloat roughness = mip / 4.0;
				shader->uniform1f("roughness", roughness);
				glViewport(0, 0, mip_size, mip_size);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mip_size, mip_size);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
				for (int i = 0; i < 6; i++)
				{
					shader->uniformMat("model", views[i]);
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, _cubeMapID, mip);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					Graphics::Graphics::cube->render();
				}
			}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void    Cubemap::renderUpdate(void)
		{

		}

		void    Cubemap::render(void)
		{
			glDisable(GL_CULL_FACE);
			glDisable(GL_DEPTH_TEST);
			glm::mat4 view = BeerEngine::Camera::main->transform.getMat4(true);
			glm::mat4 trs = glm::translate(glm::mat4(), BeerEngine::Camera::main->transform.position);

			_shader->bind();
			_shader->uniformMat("projection", Window::GetInstance()->getProjection3D());
			_shader->uniformMat("view", view);
			_shader->uniformMat("model", trs);

			glActiveTexture(GL_TEXTURE0);
			_shader->uniform1i("env_map", 0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeMapID);

//			_envMap->bind();

			Graphics::Graphics::cube->render();

			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			_shader->unbind();

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
		}

		void	Cubemap::bind()
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeMapID);
		}

		void	Cubemap::unbind()
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}

		nlohmann::json	Cubemap::serialize()
		{
			return {};
		}

		void Cubemap::deserialize(const nlohmann::json & j)
		{

		}

		Cubemap *Cubemap::Deserialize(const nlohmann::json & j)
		{
			return NULL;
		}
	}
}