//
// Created by mploux on 12/05/18.
//

#include <Core/Graphics/Graphics.hpp>
#include "Core/Graphics/Lights/AmbiantLight.hpp"
#include "Core/Graphics/Lights/ALight.hpp"
#include "Core/Graphics/ShaderProgram.hpp"
#include "Core/Window.hpp"
#include "Core/Camera.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		AmbiantLight::AmbiantLight(int id, AScene &scene)
			: ALight(id, scene)
		{
			_shader = Graphics::Graphics::lightShader;
			setupUniformIds();
		}

		AmbiantLight::AmbiantLight(float intensity, glm::vec4 color)
			: ALight(intensity, color)
		{
			_shader = Graphics::Graphics::lightShader;
			setupUniformIds();
		}

		void 	AmbiantLight::bind()
		{
			_shader->bind();
			_shader->uniformMat(_projectionShaderID, Window::GetInstance()->getProjection3D());
			glm::mat4 view = Camera::main->transform.getMat4(true);
			_shader->uniformMat(_viewShaderID, view);
			_shader->uniform4f("light.color", _color);
			_shader->uniform1f("light.intensity", _intensity);
			_shader->uniform1i("hasDirectionalLight", 0);
		}

		nlohmann::json	AmbiantLight::serialize()
		{
			return {};
		}

		void AmbiantLight::deserialize(const nlohmann::json & j)
		{

		}

		AmbiantLight * AmbiantLight::Deserialize(const nlohmann::json & j)
		{
			return nullptr;
		}
	}
}
