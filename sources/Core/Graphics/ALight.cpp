#include "Core/Graphics/ALight.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		ALight::ALight(glm::vec3 position, glm::vec3 direction, float intensity, glm::vec4 color)
			: _position(position), _direction(direction), _intensity(intensity), _color(color)
		{}

		ALight			&ALight::setColor(glm::vec4 color)
		{
			_color = color;
			return (*this);
		}
		
		ALight			&ALight::setPosition(glm::vec3 *pos)
		{
			_position = pos;
			return (*this);
		}
		
		ALight			&ALight::setDirection(glm::vec3 *dir)
		{
			_direction = dir;
			return (*this);
		}
		
		ALight			&ALight::setIntensity(float *val)
		{
			_intensity = val;
			return (*this);
		}

		const glm::vec4		&ALight::getColor() const
		{
			return (_color);
		}

		const glm::vec3		&ALight::getPosition() const
		{
			return (_position);
		}

		const glm::vec3		&ALight::getDirection() const
		{
			return (_direction);
		}

		float			ALight::getIntensity() const
		{
			return (_intensity);
		}
		
		
		nlohmann::json	ALight::serialize()
		{

		}
		
		void ALight::deserialize(const nlohmann::json & j)
		{

		}
		
		ALight * ALight::Deserialize(const nlohmann::json & j)
		{
		}
	}
}
