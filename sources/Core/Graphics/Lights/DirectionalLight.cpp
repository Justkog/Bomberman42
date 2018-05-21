//
// Created by mploux on 12/05/18.
//

#include <Core/Graphics/Graphics.hpp>
#include "Core/Graphics/Lights/DirectionalLight.hpp"
#include "Core/Graphics/Lights/ALight.hpp"
#include "Core/Graphics/ShaderProgram.hpp"
#include "Core/Window.hpp"
#include "Core/Camera.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		DirectionalLight::DirectionalLight(int id, AScene &scene)
				: ALight(id, scene), _direction(glm::vec3(1, 0, 0))
		{
			_shader = Graphics::Graphics::lightShader;
			_castShadows = true;
			_shadowMap = new Framebuffer(2048, 2048);
			_lightProjection = glm::ortho(-25.0f, 12.0f, -10.0f, 28.0f, -15.0f, 25.0f);
			setupUniformIds();
		}

		DirectionalLight::DirectionalLight(glm::vec3 direction, float intensity, glm::vec4 color)
				: ALight(intensity, color), _direction(direction)
		{
			_shader = Graphics::Graphics::lightShader;
			_castShadows = true;
			_shadowMap = new Framebuffer(2048, 2048);
			_lightProjection = glm::ortho(-25.0f, 12.0f, -10.0f, 28.0f, -15.0f, 25.0f);
			setupUniformIds();
		}

		DirectionalLight::DirectionalLight()
		{}

		DirectionalLight::DirectionalLight(const DirectionalLight &val)
		{
			*this = val;
		}

		DirectionalLight &DirectionalLight::operator=(const DirectionalLight &val)
		{
			if (this != &val)
			{
				DirectionalLight::~DirectionalLight();
				_direction = val._direction;
				_castShadows = val._castShadows;
				_shadowMap = val._shadowMap;
				_lightMatrix = val._lightMatrix;
			}
			return (*this);
		}

		DirectionalLight::~DirectionalLight()
		{
			if (_shadowMap)
			{
				delete _shadowMap;
			}
		}

		void 	DirectionalLight::bind()
		{
			glm::mat4 view = Camera::main->transform.getMat4(true);

            view = glm::lookAt(glm::vec3(0, 0, 0), _direction * -1, glm::vec3(0, 1, 0));
			_lightMatrix = _lightProjection * view;
			_shader->uniformMat("lightMatrix", _lightMatrix);

			_shader->uniform4f("directionalLight.light.color", _color);
			_shader->uniform1f("directionalLight.light.intensity", _intensity);
			_shader->uniform3f("directionalLight.direction", _direction);
			_shader->uniform1i("hasDirectionalLight", 1);

			if (_castShadows && _shadowMap)
			{
				_shader->uniform1i("shadowMap", 10);
				glActiveTexture(GL_TEXTURE10);
				glBindTexture(GL_TEXTURE_2D, _shadowMap->getDepthTextureID());
			}
		}

		DirectionalLight	&DirectionalLight::setDirection(const glm::vec3 &dir)
		{
			_direction = dir;
			return (*this);
		}

		const glm::vec3		&DirectionalLight::getDirection() const
		{
			return (_direction);
		}

		void 	DirectionalLight::bindShadowMap()
		{
			if (!_castShadows)
				return;
			_shadowMap->bindDepth();
		}

		void 	DirectionalLight::unbindShadowMap()
		{
			if (!_castShadows)
				return;
			_shadowMap->unbind();
		}

		void	DirectionalLight::setCastShadows(bool val)
		{
			_castShadows = val;
		}

		bool	DirectionalLight::isCastShadows()
		{
			return _castShadows;
		}

		void	DirectionalLight::drawShadowMap()
		{
			Graphics::Graphics::defaultGuiShader->bind();
			glBindTexture(GL_TEXTURE_2D, _shadowMap->getDepthTextureID());
			Graphics::Graphics::cube->render();
			glBindTexture(GL_TEXTURE_2D, 0);
			Graphics::Graphics::defaultGuiShader->unbind();
		}

		const glm::mat4		&DirectionalLight::getLightProjection() const
		{
			return _lightProjection;
		}

		const glm::mat4		&DirectionalLight::getLightMatrix() const
		{
			return _lightMatrix;
		}

		nlohmann::json	DirectionalLight::serialize()
		{
			return {};
		}

		void DirectionalLight::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			(void) j;
			(void) loader;
		}

		DirectionalLight * DirectionalLight::Deserialize(const nlohmann::json & j)
		{
			(void) j;
			return nullptr;
		}
	}
}
