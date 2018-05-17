#include "Core/Graphics/AMaterial.hpp"
#include "Core/Graphics/Lights/ALight.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Window.hpp"
#include "Core/Camera.hpp"
#include "Core/Graphics/ShaderProgram.hpp"
#include "Core/Graphics/Texture.hpp"
#include "Core/Json/Json.hpp"
#include "Core/IO/FileUtils.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		AMaterial::AMaterial(ShaderProgram *shader, glm::vec4 color) :
			_shader(shader),
			_color(color),
			_albedo(nullptr),
			_normal(nullptr),
			_bump(nullptr),
			_rought(nullptr),
			_metalic(nullptr),
			_roughtFactor(0.8f),
			_metalicFactor(0.5f),
			_envMap(Graphics::defaultCubemap)
		{
			shader->bind();
			_projectionShaderID = _shader->getUniformLocation("projection");
			_viewShaderID = _shader->getUniformLocation("view");
			_modelShaderID = _shader->getUniformLocation("model");

			_viewPosID = _shader->getUniformLocation("viewPos");
			_viewDirID = _shader->getUniformLocation("viewDir");

			_colorShaderID = _shader->getUniformLocation("color");
			_albedoID = _shader->getUniformLocation("albedo");
			_hasAlbedoID = _shader->getUniformLocation("hasAlbedo");
			_normalID = _shader->getUniformLocation("normal");
			_hasNormalID = _shader->getUniformLocation("hasNormal");
			_bumpID = _shader->getUniformLocation("bump");
			_hasBumpID = _shader->getUniformLocation("hasBump");

//			_lightPosID = _shader->getUniformLocation("light.position");
//			_lightDirID = _shader->getUniformLocation("light.direction");
//			_lightIntensityID = _shader->getUniformLocation("light.intensity");
//			_lightColorID = _shader->getUniformLocation("light.color");
		}

		void	AMaterial::bind(glm::mat4 &model)
		{
			// static glm::mat4 identity(1.0f);
			_shader->bind();
			_shader->uniformMat(_projectionShaderID, Window::GetInstance()->getProjection3D());
			glm::mat4 view = Camera::main->transform.getMat4(true);
			_shader->uniformMat(_viewShaderID, view);
			_shader->uniformMat(_modelShaderID, model);
			// View Pos
			glm::vec3 viewPos = Camera::main->transform.position;
			_shader->uniform3f(_viewPosID, viewPos[0], viewPos[1], viewPos[2]);
			glm::vec3 viewDir = Camera::main->transform.forward();
			_shader->uniform3f(_viewDirID, viewDir[0], viewDir[1], viewDir[2]);

			_shader->uniform4f(_colorShaderID, _color[0], _color[1], _color[2], _color[3]);

			_shader->uniform1i(_bumpID, 2);
			glActiveTexture(GL_TEXTURE2);
			if (_bump != nullptr)
			{
				_shader->uniform1i(_hasBumpID, 1);
				_bump->bind();
			}
			else
				_shader->uniform1i(_hasBumpID, 0);

			_shader->uniform1i(_normalID, 1);
			glActiveTexture(GL_TEXTURE1);
			if (_normal != nullptr)
			{
				_shader->uniform1i(_hasNormalID, 1);
				_normal->bind();
			}
			else
				_shader->uniform1i(_hasNormalID, 0);

			_shader->uniform1i(_albedoID, 0);
			glActiveTexture(GL_TEXTURE0);
			if (_albedo != nullptr)
			{
				_shader->uniform1i(_hasAlbedoID, 1);
				_albedo->bind();
			}
			else
				_shader->uniform1i(_hasAlbedoID, 0);
		}

		void	AMaterial::bind(glm::mat4 &model, ALight &light)
		{
			light.getShader().uniformMat(light.get_modelShaderID(), model);
			// View Pos
			glm::vec3 viewPos = Camera::main->transform.position;
			light.getShader().uniform3f(light.get_viewPosID(), viewPos[0], viewPos[1], viewPos[2]);
			glm::vec3 viewDir = Camera::main->transform.forward();
			light.getShader().uniform3f(light.get_viewDirID(), viewDir[0], viewDir[1], viewDir[2]);

			light.getShader().uniform4f(light.get_colorShaderID(), _color[0], _color[1], _color[2], _color[3]);

			light.getShader().uniform1i(light.get_bumpID(), 2);
			glActiveTexture(GL_TEXTURE2);
			if (_bump != nullptr)
			{
				light.getShader().uniform1i(light.get_hasBumpID(), 1);
				_bump->bind();
			}
			else
				light.getShader().uniform1i(light.get_hasBumpID(), 0);

			light.getShader().uniform1i(light.get_normalID(), 1);
			glActiveTexture(GL_TEXTURE1);
			if (_normal != nullptr)
			{
				light.getShader().uniform1i(light.get_hasNormalID(), 1);
				_normal->bind();
			}
			else
				light.getShader().uniform1i(light.get_hasNormalID(), 0);

			light.getShader().uniform1i(light.get_albedoID(), 0);
			glActiveTexture(GL_TEXTURE0);
			if (_albedo != nullptr)
			{
				light.getShader().uniform1i(light.get_hasAlbedoID(), 1);
				_albedo->bind();
			}
			else
				light.getShader().uniform1i(light.get_hasAlbedoID(), 0);

			light.getShader().uniform1i(light.get_envMapID(), 3);
			glActiveTexture(GL_TEXTURE3);
			if (_envMap != nullptr)
			{
				light.getShader().uniform1i(light.get_hasEnvMapID(), 1);
				_envMap->bind();
			}
			else
				light.getShader().uniform1i(light.get_hasEnvMapID(), 0);

			light.getShader().uniform1i("routgh", 4);
			glActiveTexture(GL_TEXTURE4);
			if (_rought != nullptr)
			{
				light.getShader().uniform1i("hasRoutgh", 1);
				_rought->bind();
			}
			else
			{
				light.getShader().uniform1i("hasRoutgh", 0);
				light.getShader().uniform1f("rougthFactor", _roughtFactor);
			}

			light.getShader().uniform1i("metalic", 5);
			glActiveTexture(GL_TEXTURE5);
			if (_metalic != nullptr)
			{
				light.getShader().uniform1i("hasMetalic", 1);
				_metalic->bind();
			}
			else
			{
				light.getShader().uniform1i("hasMetalic", 0);
				light.getShader().uniform1f("metalicFactor", _metalicFactor);
			}
		}

		AMaterial		&AMaterial::setColor(glm::vec4 color)
		{
			_color = color;
			return (*this);
		}

		AMaterial		&AMaterial::setAlbedo(Texture *tex)
		{
			_albedo = tex;
			return (*this);
		}

		AMaterial		&AMaterial::setNormal(Texture *tex)
		{
			_normal = tex;
			return (*this);
		}

		AMaterial		&AMaterial::setBump(Texture *tex)
		{
			_bump = tex;
			return (*this);
		}

		AMaterial		&AMaterial::setEnvmap(Cubemap *map)
		{
			_envMap = map;
			return (*this);
		}

		ShaderProgram	&AMaterial::getShader()
		{
			return (*_shader);
		}

		nlohmann::json	AMaterial::serialize()
		{
			auto j = JsonSerializable::serialize();
			j.merge_patch({
				{"albedo", _albedo},
				{"normal", _normal},
				{"bump", _bump},
				{"color", _color},
				{"shader", _shader},
			});
			return j;
		}

		void AMaterial::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			this->JsonSerializable::deserialize(j, loader);
			if (j.find("albedo") != j.end())
				this->setAlbedo(Texture::Deserialize(j.at("albedo"), loader));
			if (j.find("normal") != j.end())
				this->setNormal(Texture::Deserialize(j.at("normal"), loader));
			if (j.find("bump") != j.end())
				this->setBump(Texture::Deserialize(j.at("bump"), loader));
			this->setColor(j.at("color"));
		}

		AMaterial * AMaterial::Deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			auto material = new AMaterial(ShaderProgram::Deserialize(j.at("shader"), loader));
			material->deserialize(j, loader);
			
			return material;
		}
	}
}