#ifndef BE_CORE_GRAPHICS_AMATERIAL_HPP
#define BE_CORE_GRAPHICS_AMATERIAL_HPP 1

#include "../Maths/Maths.hpp"
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
			Maths::Vector4f	_color;
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
			GLint	_viewDirID;
		
		public:
			AMaterial(ShaderProgram *shader, Maths::Vector4f color = Maths::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
			virtual ~AMaterial() {};
			virtual void	bind(Maths::Matrix4x4 &model);
			AMaterial		&setColor(Maths::Vector4f color);
			AMaterial		&setAlbedo(Texture *tex);
			AMaterial		&setNormal(Texture *tex);
			AMaterial		&setBump(Texture *tex);
		};
	}
}

#endif