#include "Core/Component/ParticleBase.hpp"
#include "Core/GameObject.hpp"
#include "Core/Time.hpp"
#include "Core/Camera.hpp"
#include "Core/Window.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Mathf.hpp"

namespace BeerEngine
{
	namespace Component
	{
		ParticleBase::ParticleBase(GameObject *gameObject) :
			Component(gameObject),
			_mesh(nullptr),
			_particles()
		{
			texture = Graphics::Graphics::whiteTexture;
			_particlePositionBuffer = new glm::vec3[BE_PARTICLESSYSTEM_MAX];
			_particleUVBuffer = new glm::vec2[BE_PARTICLESSYSTEM_MAX];
			_particleColorBuffer = new glm::vec4[BE_PARTICLESSYSTEM_MAX];
			_particleSizeBuffer = new float[BE_PARTICLESSYSTEM_MAX];
			_particleCount = 0;

			// Init Variable for particle
			spawnTime = 1.0f;
			lifeTime = 1.0f;
			color0 = glm::vec4(1);
			color1 = glm::vec4(1);
			velocity = glm::vec3(0, 5.0f, 5.0f);
			size0 = 1.0f;
			size1 = 1.0f;
			anim = false;
			animTotalFrame = 1;
			animFrameWidth = 1;
			animFrameHeight = 1;
			offset = glm::vec3();
		}

		ParticleBase::ParticleBase()
		{}

		ParticleBase::ParticleBase(const ParticleBase &val)
		{
			*this = val;
		}
		
		ParticleBase &ParticleBase::operator=(const ParticleBase &val)
		{
			if (this != &val)
			{
				_mesh = val._mesh;
				_particlePositionBuffer = val._particlePositionBuffer;
				_particleUVBuffer = val._particleUVBuffer;
				_particleColorBuffer = val._particleColorBuffer;
				_particleSizeBuffer = val._particleSizeBuffer;
				_particleCount = val._particleCount;
				_projectionShaderID = val._projectionShaderID;
				_viewShaderID = val._viewShaderID;
				_modelShaderID = val._modelShaderID;
				_spriteID = val._spriteID;
				_spriteUVSizeID = val._spriteUVSizeID;
			}
			return (*this);
		}

		ParticleBase::~ParticleBase()
		{
			_particles.clear();
			delete _particlePositionBuffer;
			delete _particleUVBuffer;
			delete _particleColorBuffer;
			delete _particleSizeBuffer;
			delete _mesh;
		}

		void	ParticleBase::addParticle(void)
		{
			if (_particles.size() + 1 >= BE_PARTICLESSYSTEM_MAX)
					return ;
			_particles.push_back(Particle());
			int id = _particles.size() - 1;
			initParticle(_particles[id]);
		}

		void    ParticleBase::fixedUpdate(void)
		{}

		void    ParticleBase::update(void)
		{
			static float spawnTimeRate = 0.0f;
			float delta = Time::GetDeltaTime();
			spawnTimeRate += delta;
			// std::cout << spawnTimeRate << " // " << spawnTime << std::endl;
			while (spawnTimeRate >= spawnTime)
			{
				addParticle();
				spawnTimeRate -= spawnTime;
			}

			std::size_t i = 0;
			while (i < _particles.size())
			{
				_particles[i].life -= delta;
				if (_particles[i].life > 0.0f)
				{
					upgradeParticle(_particles[i], delta);
					i++;
				}
				else
					_particles.erase(_particles.begin() + i);
			}
			// std::cout << _particles.size() << std::endl;
		}

		void    ParticleBase::renderAlphaUpdate(void)
		{
			if (_mesh == nullptr)
			{
				_mesh = new Graphics::Mesh(6);
				static const glm::vec3 vertPos[] = {
					glm::vec3(-0.5, -0.5, 0.0),
					glm::vec3(0.5, -0.5, 0.0),
					glm::vec3(0.5, 0.5, 0.0),
					glm::vec3(0.5, 0.5, 0.0),
					glm::vec3(-0.5, 0.5, 0.0),
					glm::vec3(-0.5, -0.5, 0.0)
				};
				_mesh->add(0, GL_FLOAT, 3, (void *)vertPos, 6);
				static float s = 1.0f;
				static const glm::vec2 vertUV[] = {
					glm::vec2(0, 0),
					glm::vec2(s, 0),
					glm::vec2(s, s),
					glm::vec2(s, s),
					glm::vec2(0, s),
					glm::vec2(0, 0),
				};
				_mesh->add(1, GL_FLOAT, 2, (void *)vertUV, 6);
				_mesh->add(2, GL_FLOAT, 3, NULL, BE_PARTICLESSYSTEM_MAX, GL_STREAM_DRAW);
				_mesh->add(3, GL_FLOAT, 2, NULL, BE_PARTICLESSYSTEM_MAX, GL_STREAM_DRAW);
				_mesh->add(4, GL_FLOAT, 4, NULL, BE_PARTICLESSYSTEM_MAX, GL_STREAM_DRAW);
				_mesh->add(5, GL_FLOAT, 1, NULL, BE_PARTICLESSYSTEM_MAX, GL_STREAM_DRAW);
				_mesh->setSize(6);

				Graphics::Graphics::particleShader->bind();
				_projectionShaderID = Graphics::Graphics::particleShader->getUniformLocation("projection");
				_viewShaderID = Graphics::Graphics::particleShader->getUniformLocation("view");
				_modelShaderID = Graphics::Graphics::particleShader->getUniformLocation("model");
				_spriteID = Graphics::Graphics::particleShader->getUniformLocation("sprite");
				_spriteUVSizeID = Graphics::Graphics::particleShader->getUniformLocation("UVSize");
				return;
			}
			_particleCount = 0;
			for (std::size_t i = 0; i < _particles.size(); i++)
			{
				float u = 0.0f;
				float v = 0.0f;
				// Animate
				if (anim)
				{
					int j = (int)(_particles[i].lifeAnim * 100);
					j = j % animTotalFrame;
					u = (float)(j % animFrameWidth) / (float)animFrameWidth;
					v = (float)(j / animFrameWidth) / (float)animFrameWidth;
				}
				float lifeProgress = 1.0f - (_particles[i].life / lifeTime);
				glm::vec4 color = glm::lerp(color0, color1, lifeProgress);
				_particlePositionBuffer[_particleCount] = _particles[i].position;
				_particleUVBuffer[_particleCount] = glm::vec2(u, v);
				_particleColorBuffer[_particleCount] = color;
				float size = glm::lerp(size0, size1, lifeProgress);
				_particleSizeBuffer[_particleCount] = size;
				_particleCount++;
			}
			_mesh->add(2, GL_FLOAT, 3, (void *)_particlePositionBuffer, _particleCount, GL_STREAM_DRAW);
			_mesh->add(3, GL_FLOAT, 2, (void *)_particleUVBuffer, _particleCount, GL_STREAM_DRAW);
			_mesh->add(4, GL_FLOAT, 4, (void *)_particleColorBuffer, _particleCount, GL_STREAM_DRAW);
			_mesh->add(5, GL_FLOAT, 1, (void *)_particleSizeBuffer, _particleCount, GL_STREAM_DRAW);
			_mesh->setSize(6);
		}

		void    ParticleBase::renderAlpha(void)
		{
			static int	divisor[] {
				0, 0, 1, 1, 1, 1
			};
			if (_mesh == nullptr)
				return ;
			glEnable(GL_ALPHA_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glDepthMask(GL_FALSE);
			
			Graphics::Graphics::particleShader->bind();
			Graphics::Graphics::particleShader->uniformMat(_projectionShaderID, Window::GetInstance()->getProjection3D());
			glm::mat4 view = Camera::main->transform.getMat4(true);
			Graphics::Graphics::particleShader->uniformMat(_viewShaderID, view);
			glm::mat4 model = _gameObject->transform.getMat4();
			Graphics::Graphics::particleShader->uniformMat(_modelShaderID, model);
			Graphics::Graphics::particleShader->uniform1i(_spriteID, 0);
			Graphics::Graphics::particleShader->uniform2f(_spriteUVSizeID, 1.0f / (float)animFrameWidth, 1.0f / (float)animFrameHeight);
			
			glActiveTexture(GL_TEXTURE0);
			texture->bind();
			_mesh->render(GL_TRIANGLES, true, _particleCount, (int *)divisor, 6);
			glDepthMask(GL_TRUE);
//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_BLEND);
		}


		void	ParticleBase::setTexture(Graphics::Texture *t)
		{
			texture = t;
		}

		void 	ParticleBase::initParticle(Particle &particle)
		{
			particle.life = lifeTime;
			particle.position = _gameObject->transform.getWorldPosition() + offset;
			particle.velocity = _gameObject->transform.getWorldRotate(velocity);
			particle.lifeAnimSpeed = ((float)rand() / RAND_MAX) + 0.9f;
		}

		void 	ParticleBase::upgradeParticle(Particle &particle, float delta)
		{
			particle.lifeAnim += particle.lifeAnimSpeed * delta;
			particle.position += particle.velocity * delta;
		}

		ParticleBase	&ParticleBase::setSpawnTime(GLfloat stime)
		{
			spawnTime = stime;
			if (spawnTime < 0.0f)
				spawnTime = 1.0f;
			return (*this);	
		}

		ParticleBase	&ParticleBase::setLifeTime(GLfloat life)
		{
			lifeTime = life;
			if (lifeTime < 0.0f)
				lifeTime = 1.0f;
			return (*this);	
		}

		ParticleBase	&ParticleBase::setColor(glm::vec4 c0)
		{
			color0 = c0;
			color1 = c0;
			return (*this);	
		}

		ParticleBase	&ParticleBase::setColor(glm::vec4 c0, glm::vec4 c1)
		{	
			color0 = c0;
			color1 = c1;
			return (*this);	
		}

		ParticleBase	&ParticleBase::setVelocity(glm::vec3 vel)
		{
			velocity = vel;
			return (*this);	
		}

		ParticleBase	&ParticleBase::setSize(float s)
		{
			if (s > 0.0f)
			{
				size0 = s;
				size1 = s;
			}
			return (*this);
		}
		ParticleBase	&ParticleBase::setSize(float s0, float s1)
		{
			if (s0 > 0.0f)
			{
				size0 = s0;
				size1 = s0;
			}
			if (s1 > 0.0f)
				size1 = s1;
			return (*this);
		}

		ParticleBase	&ParticleBase::setAnimate(bool a, int aTotalFrame, int aFrameWidth, int aFrameHeight)
		{
			anim = a;
			animTotalFrame = aTotalFrame;
			animFrameWidth = aFrameWidth;
			animFrameHeight = aFrameHeight;
			return (*this);	
		}

		nlohmann::json	ParticleBase::serialize()
		{
			// TODO
			auto j = Component::serialize();
			j.merge_patch({
				{"componentClass", type},
			});
			return j;
		}

		void ParticleBase::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			// TODO
			this->Component::deserialize(j, loader);
		}

		REGISTER_COMPONENT_CPP(ParticleBase)
	}
}