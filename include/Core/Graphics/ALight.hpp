#ifndef BE_CORE_GRAPHICS_ALIGHT_HPP
#define BE_CORE_GRAPHICS_ALIGHT_HPP 1

#include "Core/Core.hpp"
#include "Core/Json/JsonSerializable.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		class ALight : public JsonSerializable
		{
		private:
			glm::vec3	_position;
			glm::vec3	_direction;
			float		_intensity;
			glm::vec4	_color;

			GLint	_colorShaderID;
			GLint	_albedoID;
			GLint	_hasAlbedoID;
			GLint	_normalID;

		public:
			ALight(glm::vec3 position, glm::vec3 direction = glm::vec3(0, 0, 1), float intensity = 1.0f, glm::vec4 color = glm::vec4(1.0f));
			virtual ~ALight() {};
			ALight			&setColor(glm::vec4 color);
			ALight			&setPosition(Texture *tex);
			ALight			&setDirection(Texture *tex);
			ALight			&setIntensity(Texture *tex);

			const glm::vec4		&ALight::getColor() const;
			const glm::vec3		&ALight::getPosition() const;
			const glm::vec3		&ALight::getDirection() const;
			float				ALight::getIntensity() const;

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);
			static ALight * Deserialize(const nlohmann::json & j);
		};
	}
}

#endif