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
			_albedo(nullptr)
		{
			shader->bind();
			_projectionShaderID = _shader->getUniformLocation("projection");
			_viewShaderID = _shader->getUniformLocation("view");
			_modelShaderID = _shader->getUniformLocation("model");
			_colorShaderID = _shader->getUniformLocation("color");
			_albedoID = _shader->getUniformLocation("albedo");
		}

		void	AMaterial::bind(glm::mat4 &model)
		{
			// static glm::mat4 identity(1.0f);
			_shader->bind();
			_shader->uniformMat(_projectionShaderID, Window::GetInstance()->getProjection3D());
			glm::mat4 view = Camera::main->transform.getMat4(true);
			_shader->uniformMat(_viewShaderID, view);
			_shader->uniformMat(_modelShaderID, model);
			_shader->uniform4f(_colorShaderID, _color[0], _color[1], _color[2], _color[3]);

			_shader->uniform1i(_albedoID, 0);
			glActiveTexture(GL_TEXTURE0);
			if (_albedo != nullptr)
				_albedo->bind();
			else
				Graphics::whiteTexture->bind();
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
	}
}