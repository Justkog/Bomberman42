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
			_shader = Graphics::Graphics::directionalShader;
			setupUniformIds();
		}

		DirectionalLight::DirectionalLight(glm::vec3 direction, float intensity, glm::vec4 color)
				: ALight(intensity, color), _direction(direction)
		{
			_shader = Graphics::Graphics::directionalShader;
			setupUniformIds();
		}

		void 	DirectionalLight::bind()
		{
			_shader->bind();
			_shader->uniformMat(_projectionShaderID, Window::GetInstance()->getProjection3D());
			glm::mat4 view = Camera::main->transform.getMat4(true);
			_shader->uniformMat(_viewShaderID, view);

			_shader->uniform4f("light.light.color", _color);
			_shader->uniform1f("light.light.intensity", _intensity);
			_shader->uniform3f("light.direction", _direction);

			_shader->uniform1f(_specularPowerID, _specularity.power);
			_shader->uniform1f(_specularIntensityID, _specularity.intensity);
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

		nlohmann::json	DirectionalLight::serialize()
		{

		}

		void DirectionalLight::deserialize(const nlohmann::json & j)
		{

		}

		DirectionalLight * DirectionalLight::Deserialize(const nlohmann::json & j)
		{
		}
	}
}
