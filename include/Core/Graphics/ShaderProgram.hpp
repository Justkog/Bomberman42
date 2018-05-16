#ifndef BE_CORE_GRAPHICS_SHADERPROGRAM_HPP
#define BE_CORE_GRAPHICS_SHADERPROGRAM_HPP 1
/*!
 * \file ShaderProgram.hpp
 * \brief Programme permettant de charger et d'utiliser les scripts glsl
 * \author mgallo, mploux, jblondea
 */
#include "../Core.hpp"
#include "Core/Json/JsonSerializable.hpp"
/*! \namespace BeerEngine
 * 
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
	/*! \namespace Graphics
	* espace de nommage regroupant les fonctionnalité graphique du moteur
	*/
	namespace Graphics
	{
		/*! \class ShaderProgram
		* \brief Cette class permet de charger et compiler les scripts pour la carte graphique (glsl), puis de les utiliser pour le traitement des rendus
		*/
		class ShaderProgram : public JsonSerializable
		{
		private:
			int				_size;
			GLuint			_program;
			GLuint			*_shaders;
			std::string		_sourceFileVS;
			std::string		_sourceFileFS;

		public:
			ShaderProgram(int size);
			~ShaderProgram(void);
			void			load(unsigned int shaderIndex, GLenum shaderType, const char *script);
			void			compile(void);
			void			bind(void);
			void			unbind(void);
			static void		Unbind(void);
			GLint			getUniformLocation(std::string const &name);
			void			uniform1i(std::string const &name, int i);
			void			uniform1i(GLint id, int i);
			void			uniform1f(std::string const &name, float x);
			void			uniform1f(GLint id, float x);
			void			uniform2f(std::string const &name, float x, float y);
			void			uniform2f(GLint id, float x, float y);
			void			uniform2f(std::string const &name, float *data);
			void			uniform2f(std::string const &name, glm::vec2 const &vec);
			void			uniform3f(std::string const &name, float x, float y, float z);
			void			uniform3f(GLint id, float x, float y, float z);
			void			uniform3f(GLint id, glm::vec3 const &vec);
			void			uniform3f(std::string const &name, glm::vec3 const &vec);
			void			uniform3f(std::string const &name, float *data);
			void			uniform4f(std::string const &name, glm::vec4 const &vec);
			void			uniform4f(std::string const &name, float x, float y, float z, float w);
			void			uniform4f(GLint id, float x, float y, float z, float w);
			void			uniform4f(GLint id, glm::vec4 const &vec);
			void			uniform4f(std::string const &name, float *data);
			void			uniformMat(std::string const &name, glm::mat4 &mat);
			void			uniformMat(GLint id, glm::mat4 &mat);

			static ShaderProgram	*LoadShader(std::string pathVS, std::string pathFS);

			nlohmann::json	serialize();
			static ShaderProgram * Deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader);
			
			static std::string  	LoadShaderSource(std::string const &path);
		};
	}
}

#endif