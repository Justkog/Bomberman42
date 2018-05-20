//
// Created by mploux on 12/05/18.
//

#ifndef BE_CORE_GRAPHICS_DIRECTIONALLIGHT_HPP
#define BE_CORE_GRAPHICS_DIRECTIONALLIGHT_HPP 1
/*!
 * \file DirectionalLight.hpp
 * \brief Fonctionnaliter de la lumierer directionnel
 * \author mploux
 */
#include "Core/Core.hpp"
#include "Core/Json/JsonSerializable.hpp"
#include "ALight.hpp"
#include "../Framebuffer.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		/*! \class DirectionalLight
		* \brief Extension des lumieres basique pour une lumiere directionnel (ex: le soleil)
		*/
		class DirectionalLight : public ALight
		{
		private:
			glm::vec3		_direction;
			bool			_castShadows;
			Framebuffer		*_shadowMap;
			glm::mat4		_lightMatrix;

		public:
			DirectionalLight();
			DirectionalLight(const DirectionalLight &val);
			DirectionalLight &operator=(const DirectionalLight &val);

			DirectionalLight(int id, AScene &scene);
			DirectionalLight(glm::vec3 direction, float intensity, glm::vec4 color);
			virtual ~DirectionalLight();

			void 	bind();

			void 	bindShadowMap();
			void 	unbindShadowMap();

			DirectionalLight	&setDirection(const glm::vec3 &dir);
			const glm::vec3		&getDirection() const;

			void	setCastShadows(bool val);
			bool	isCastShadows();

			void	drawShadowMap();

			nlohmann::json	serialize();
			void deserialize(const nlohmann::json & j);
			static DirectionalLight * Deserialize(const nlohmann::json & j);
		};
	}
}

#endif //BE_CORE_GRAPHICS_DIRECTIONALLIGHT_HPP