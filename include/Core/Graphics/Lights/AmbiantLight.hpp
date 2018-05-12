//
// Created by mploux on 12/05/18.
//

#ifndef BE_CORE_GRAPHICS_AMBIANTLIGHT_HPP
#define BE_CORE_GRAPHICS_AMBIANTLIGHT_HPP 1

#include "Core/Core.hpp"
#include "Core/Json/JsonSerializable.hpp"
#include "ALight.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		class AmbiantLight : public ALight
		{
		public:
			AmbiantLight(int id, AScene &scene);
			AmbiantLight(float intensity, glm::vec4 color);
			virtual ~AmbiantLight() {};

			void 	bind();

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);
			static AmbiantLight * Deserialize(const nlohmann::json & j);
		};
	}
}

#endif //BE_CORE_GRAPHICS_AMBIANTLIGHT_HPP
