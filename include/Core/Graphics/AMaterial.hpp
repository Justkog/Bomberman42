#ifndef BE_CORE_GRAPHICS_AMATERIAL_HPP
#define BE_CORE_GRAPHICS_AMATERIAL_HPP 1

#include "Core/Core.hpp"
#include "Core/Json/JsonSerializable.hpp"
#include "Cubemap.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		class AMaterial : public JsonSerializable
		{
		private:
			ShaderProgram	*_shader;
			glm::vec4		_color;
			Texture			*_albedo;
			Texture			*_normal;
			Texture			*_bump;
			Cubemap			*_envMap;

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
			GLint	_envMapID;
			GLint	_hasEnvMapID;

			GLint	_lightPosID;
			GLint	_lightDirID;
			GLint	_lightIntensityID;
			GLint	_lightColorID;
		
		public:
			AMaterial(ShaderProgram *shader, glm::vec4 color = glm::vec4(1.0f));
			virtual ~AMaterial() {};
			virtual void	bind(glm::mat4 &model);
			virtual void	bind(glm::mat4 &model, ALight &light);
			AMaterial		&setColor(glm::vec4 color);
			AMaterial		&setAlbedo(Texture *tex);
			AMaterial		&setNormal(Texture *tex);
			AMaterial		&setBump(Texture *tex);
			AMaterial		&setEnvmap(Cubemap *map);

			ShaderProgram	&getShader();

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);
			static AMaterial * Deserialize(const nlohmann::json & j);
		};
	}
}

#endif