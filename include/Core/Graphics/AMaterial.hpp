#ifndef BE_CORE_GRAPHICS_AMATERIAL_HPP
#define BE_CORE_GRAPHICS_AMATERIAL_HPP 1

#include "ShaderProgram.hpp"
#include "Texture.hpp"

namespace BeerEngine
{
	namespace Graphics
	{
		class AMaterial
		{
		private:
			ShaderProgram	*_shader;
			glm::vec4		_color;
			Texture			*_albedo;
			Texture			*_normal;
			Texture			*_bump;

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
		
		public:
			AMaterial(ShaderProgram *shader, glm::vec4 color = glm::vec4(1.0f));
			virtual ~AMaterial() {};
			virtual void	bind(glm::mat4 &model);
			AMaterial		&setColor(glm::vec4 color);
			AMaterial		&setAlbedo(Texture *tex);
			AMaterial		&setNormal(Texture *tex);
			AMaterial		&setBump(Texture *tex);
		};
	}
}

#endif