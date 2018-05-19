//
// Created by mploux on 12/05/18.
//

#ifndef BE_CORE_GRAPHICS_AMBIANTLIGHT_HPP
#define BE_CORE_GRAPHICS_AMBIANTLIGHT_HPP 1
/*!
 * \file AmbiantLight.hpp
 * \brief Fonctionnaliter de la lumierer d'ambiance
 * \author mploux
 */
#include "Core/Core.hpp"
#include "Core/Json/JsonSerializable.hpp"
#include "ALight.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		/*! \class AmbiantLight
		* \brief Extension des lumiers basique pour une lumiere d'ambiance
		*/
		class AmbiantLight : public ALight
		{
		public:
			AmbiantLight(int id, AScene &scene);
			AmbiantLight(float intensity, glm::vec4 color);
			virtual ~AmbiantLight() {};

			void 	bind();

			nlohmann::json	serialize();
			void deserialize(const nlohmann::json & j);
			static AmbiantLight * Deserialize(const nlohmann::json & j);
		};
	}
}

#endif //BE_CORE_GRAPHICS_AMBIANTLIGHT_HPP
