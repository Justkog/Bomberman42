#ifndef BE_CORE_COMPONENT_PARTICLEBASE_HPP
#define BE_CORE_COMPONENT_PARTICLEBASE_HPP 1

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IRenderAlpha.hpp"

#define BE_PARTICLESSYSTEM_MAX 30000

namespace BeerEngine
{
	namespace Component
	{
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

		class ParticleBase : public Component, public IUpdate, public IRenderAlpha
		{
		protected:
			Graphics::Mesh			*_mesh;
			std::vector<Particle>	_particles;
			glm::vec3				*_particlePositionBuffer;
			glm::vec2				*_particleUVBuffer;
			glm::vec4				*_particleColorBuffer;
			int						_particleCount;
			Graphics::Texture		*_texture;

			GLint	_projectionShaderID;
			GLint	_viewShaderID;
			GLint	_modelShaderID;
			GLint	_spriteID;
			
			void	addParticle(void);
		public:
			ParticleBase(GameObject *gameObject);
			virtual ~ParticleBase();

			void    fixedUpdate(void);
        	void    update(void);
        	void    renderUpdate(void);
        	void    render(void);
			void	setTexture(Graphics::Texture *t);

			virtual void initParticle(Particle &particle);
			virtual void upgradeParticle(Particle &particle, float delta);

		};
	}
}

#endif