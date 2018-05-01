#ifndef BE_CORE_GRAPHICS_PARTICLESSYSTEM_HPP
#define BE_CORE_GRAPHICS_PARTICLESSYSTEM_HPP 1

#include "../Core.hpp"
#include "../GameObject.hpp"
#include "Texture.hpp"
#include <vector>

#define BE_PARTICLESSYSTEM_MAX 30000

namespace BeerEngine
{
	namespace Graphics
	{
		class Mesh;

		struct Particle {
			glm::vec3 position;
			glm::vec3 velocity;
			glm::vec4 color;
			GLfloat life;
			GLfloat lifeAnim;
			GLfloat lifeAnimSpeed;
		
			Particle():
				position(0.0f),
				velocity(0.0f),
				color(1.0f),
				life(0.0f),
				lifeAnim(0.0f),
				lifeAnimSpeed(0.0f)
			{}
		};

		class ParticlesSystem : public GameObject
		{
		private:
			Mesh					*_mesh;
			std::vector<Particle>	_particles;
			glm::vec3				*_particlePositionBuffer;
			glm::vec2				*_particleUVBuffer;
			glm::vec4				*_particleColorBuffer;
			int						_particleCount;
			Texture					*texture;

			GLint	_projectionShaderID;
			GLint	_viewShaderID;
			GLint	_modelShaderID;
			GLint	_spriteID;
			
			void	addParticle(void);
		
		public:
			ParticlesSystem(int uniqueID, AScene &scene);
			virtual ~ParticlesSystem();

			void	start(void);
			void    fixedUpdate(void);
        	void    update(void);
        	void    renderUpdate(void);
        	void    render(void);
			void	setTexture(Texture *t);
		};
	}
}

#endif