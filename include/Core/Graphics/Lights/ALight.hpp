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
		public:
			struct Specular
			{
				float	power;
				float	intensity;
			};

		protected:
			ShaderProgram	*_shader;
			float			_intensity;
			glm::vec4		_color;
			Specular		_specularity;

			// Shader ID
			GLint	_colorShaderID;
			GLint	_albedoID;
			GLint	_hasAlbedoID;
			GLint	_normalID;
			GLint	_hasNormalID;
			GLint	_bumpID;
			GLint	_hasBumpID;
			GLint	_projectionShaderID;
			GLint	_viewShaderID;
			GLint	_modelShaderID;
			GLint	_viewPosID;
			GLint	_viewDirID;
			GLint	_lightPosID;
			GLint	_lightDirID;
			GLint	_lightIntensityID;
			GLint	_lightColorID;
			GLint	_specularPowerID;
			GLint	_specularIntensityID;
			GLint	_envMapID;
			GLint	_hasEnvMapID;

			void setupUniformIds();

		public:
			ALight(int id, AScene &scene);
			ALight(float intensity, glm::vec4 color);
			virtual ~ALight() {};

			virtual void 	bind() = 0;

			ALight			&setColor(glm::vec4 color);
			ALight			&setIntensity(float intensity);

			const glm::vec4		&getColor() const;
			float				getIntensity() const;

			ShaderProgram	&getShader() const;

			GLint get_colorShaderID() const;

			GLint get_albedoID() const;

			GLint get_hasAlbedoID() const;

			GLint get_normalID() const;

			GLint get_hasNormalID() const;

			GLint get_bumpID() const;

			GLint get_hasBumpID() const;

			GLint get_projectionShaderID() const;

			GLint get_viewShaderID() const;

			GLint get_modelShaderID() const;

			GLint get_viewPosID() const;

			GLint get_viewDirID() const;

			GLint get_lightPosID() const;

			GLint get_lightDirID() const;

			GLint get_lightIntensityID() const;

			GLint get_lightColorID() const;

			GLint get_specularePowerID() const;

			GLint get_speculareIntensityID() const;

			GLint get_envMapID() const;

			GLint get_hasEnvMapID() const;

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);
			static ALight * Deserialize(const nlohmann::json & j);
		};
	}
}

#endif