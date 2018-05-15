//
// Created by mploux on 12/05/18.
//

#ifndef BE_CORE_GRAPHICS_DIRECTIONALLIGHT_HPP
#define BE_CORE_GRAPHICS_DIRECTIONALLIGHT_HPP 1

#include "Core/Core.hpp"
#include "Core/Json/JsonSerializable.hpp"
#include "ALight.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		class DirectionalLight : public ALight
		{
		private:
			glm::vec3	_direction;

		public:
			DirectionalLight(int id, AScene &scene);
			DirectionalLight(glm::vec3 direction, float intensity, glm::vec4 color);
			virtual ~DirectionalLight() {};

			void 	bind();

			DirectionalLight	&setDirection(const glm::vec3 &dir);
			const glm::vec3		&getDirection() const;

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);
			static DirectionalLight * Deserialize(const nlohmann::json & j);
		};
	}
}

#endif //BE_CORE_GRAPHICS_DIRECTIONALLIGHT_HPP