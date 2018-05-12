//
// Created by mploux on 12/05/18.
//

#include <Core/Graphics/Graphics.hpp>
#include "Core/Graphics/Lights/AmbiantLight.hpp"
#include "Core/Graphics/Lights/ALight.hpp"
#include "Core/Graphics/ShaderProgram.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		AmbiantLight::AmbiantLight(int id, AScene &scene)
			: ALight(id, scene)
		{
			_shader = Graphics::Graphics::ambiantShader;
			setupUniformIds();
		}

		AmbiantLight::AmbiantLight(float intensity, glm::vec4 color)
			: ALight(intensity, color)
		{
			_shader = Graphics::Graphics::ambiantShader;
			setupUniformIds();
		}

		void 	AmbiantLight::bind()
		{
			_shader->uniform4f("light.color", _color);
			_shader->uniform1f("light.intensity", _intensity);
		}

		nlohmann::json	AmbiantLight::serialize()
		{

		}

		void AmbiantLight::deserialize(const nlohmann::json & j)
		{

		}

		AmbiantLight * AmbiantLight::Deserialize(const nlohmann::json & j)
		{
		}
	}
}
