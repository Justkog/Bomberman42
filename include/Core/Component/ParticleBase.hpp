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
			GLfloat life;
			GLfloat lifeAnim;
			GLfloat lifeAnimSpeed;
		
			Particle():
				position(0.0f),
				velocity(0.0f),
				life(0.0f),
				lifeAnim(0.0f),
				lifeAnimSpeed(0.0f)
			{}
		};

		class ParticleBase : public Component, public IUpdate, public IRenderAlpha
		{
		private:
			Graphics::Mesh			*_mesh;
			std::vector<Particle>	_particles;
			glm::vec3				*_particlePositionBuffer;
			glm::vec2				*_particleUVBuffer;
			glm::vec4				*_particleColorBuffer;
			float					*_particleSizeBuffer;
			int						_particleCount;

			GLint	_projectionShaderID;
			GLint	_viewShaderID;
			GLint	_modelShaderID;
			GLint	_spriteID;
			GLint	_spriteUVSizeID;

		protected:
			Graphics::Texture	*texture;
			GLfloat				spawnTime;
			GLfloat				lifeTime;
			glm::vec4			color0;
			glm::vec4			color1;
			glm::vec3			velocity;
			float				size0;
			float				size1;
			bool				anim;
			int					animTotalFrame;
			int					animFrameWidth;
			int					animFrameHeight;

			void	addParticle(void);

		public:
			ParticleBase(GameObject *gameObject);
			virtual ~ParticleBase();

			void    fixedUpdate(void);
        	void    update(void);
        	void    renderAlphaUpdate(void);
        	void    renderAlpha(void);
			void	setTexture(Graphics::Texture *t);

			virtual void initParticle(Particle &particle);
			virtual void upgradeParticle(Particle &particle, float delta);

			ParticleBase	&setSpawnTime(GLfloat stime);
			ParticleBase	&setLifeTime(GLfloat life);
			ParticleBase	&setColor(glm::vec4 c0);
			ParticleBase	&setColor(glm::vec4 c0, glm::vec4 c1);
			ParticleBase	&setVelocity(glm::vec3 vel);
			ParticleBase	&setSize(float s);
			ParticleBase	&setSize(float s0, float s1);
			ParticleBase	&setAnimate(bool a, int aTotalFrame = 1, int aFrameWidth = 1, int aFrameHeight = 1);

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif