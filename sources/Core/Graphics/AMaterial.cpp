#include "Core/Graphics/AMaterial.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Window.hpp"
#include "Core/Camera.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		AMaterial::AMaterial(ShaderProgram *shader, glm::vec4 color) :
			_shader(shader),
			_color(color),
			_albedo(nullptr),
			_normal(nullptr),
			_bump(nullptr)
		{
			shader->bind();
			_projectionShaderID = _shader->getUniformLocation("projection");
			_viewShaderID = _shader->getUniformLocation("view");
			_modelShaderID = _shader->getUniformLocation("model");

			_viewPosID = _shader->getUniformLocation("viewPos");

			_colorShaderID = _shader->getUniformLocation("color");
			_albedoID = _shader->getUniformLocation("albedo");
			_hasAlbedoID = _shader->getUniformLocation("hasAlbedo");
			_normalID = _shader->getUniformLocation("normal");
			_hasNormalID = _shader->getUniformLocation("hasNormal");
			_bumpID = _shader->getUniformLocation("bump");
			_hasBumpID = _shader->getUniformLocation("hasBump");
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

	}
}