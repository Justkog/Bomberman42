#include <algorithm>
#include "Core/Graphics/Particles.hpp"
#include "Core/Graphics/Mesh.hpp"
#include "Core/GameObject.hpp"
#include "Core/AScene.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Window.hpp"
#include "Core/Camera.hpp"
#include "Core/Time.hpp"


namespace BeerEngine
{
	namespace Graphics
	{
		ParticlesSystem::ParticlesSystem(int uniqueID, AScene &scene) :
			GameObject(uniqueID, scene),
			_mesh(nullptr),
			_particles()
		{
			texture = Graphics::whiteTexture;
			_particlePositionBuffer = new glm::vec3[BE_PARTICLESSYSTEM_MAX];
			_particleUVBuffer = new glm::vec2[BE_PARTICLESSYSTEM_MAX];
			_particleColorBuffer = new glm::vec4[BE_PARTICLESSYSTEM_MAX];
			_mesh = new Mesh(5);
			const glm::vec3 vertPos[] = {
				glm::vec3(-0.5, -0.5, 0.0),
				glm::vec3(0.5, -0.5, 0.0),
				glm::vec3(0.5, 0.5, 0.0),
				glm::vec3(0.5, 0.5, 0.0),
				glm::vec3(-0.5, 0.5, 0.0),
				glm::vec3(-0.5, -0.5, 0.0)
			};
			_mesh->add(0, GL_FLOAT, 3, (void *)vertPos, 6);
			float s = 1.0f / 8.0f;
			const glm::vec2 vertUV[] = {
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
			_mesh->setSize(6);
			_particleCount = 0;
			Graphics::particleShader->bind();
			_projectionShaderID = Graphics::particleShader->getUniformLocation("projection");
			_viewShaderID = Graphics::particleShader->getUniformLocation("view");
			_modelShaderID = Graphics::particleShader->getUniformLocation("model");
			_spriteID = Graphics::particleShader->getUniformLocation("sprite");
		}

		ParticlesSystem::~ParticlesSystem()
		{
			_particles.clear();
			delete _particlePositionBuffer;
			delete _particleUVBuffer;
			delete _particleColorBuffer;
			delete _mesh;
		}
		
		void	ParticlesSystem::start(void)
		{}

		void	ParticlesSystem::addParticle(void)
		{
			if (_particles.size() + 1 >= BE_PARTICLESSYSTEM_MAX)
					return ;
			_particles.push_back(Particle());
			float rx = (2.0 * ((float)rand() / RAND_MAX)) + -1;
			float rz = (0.2 * ((float)rand() / RAND_MAX)) + 1.9f;
			int id = _particles.size() - 1;
			_particles[id].position = transform.getWorldPosition();
			_particles[id].velocity = transform.getWorldRotate(glm::vec3(rx, 9.81f, rz));
			_particles[id].lifeAnimSpeed = ((float)rand() / RAND_MAX) + 0.9f;
		}

		void    ParticlesSystem::fixedUpdate(void)
		{
			// for (int i = 0; i < 10; i++)
				addParticle();
			// std::cout << _particles.size() << std::endl;
		}

		void    ParticlesSystem::update(void)
		{
			float delta = Time::GetDeltaTime();
			int i = 0;
			while (i < _particles.size())
			{
				_particles[i].life += delta;
				if (_particles[i].life <= 6.4)
				{
					_particles[i].lifeAnim += _particles[i].lifeAnimSpeed * delta;
					_particles[i].velocity += transform.getWorldRotate(glm::vec3(0.0f, -9.81f, 0.0f)) * delta;
					_particles[i].position += _particles[i].velocity * delta;
					i++;
				}
				else
					_particles.erase(_particles.begin() + i);
			}
		}

		void    ParticlesSystem::renderUpdate(void)
		{
			_particleCount = 0;
			for (int i = 0; i < _particles.size(); i++)
			{
				int j = (int)(_particles[i].lifeAnim * 100);
				j = j % 64;
				_particlePositionBuffer[_particleCount] = _particles[i].position;
				_particleUVBuffer[_particleCount] = glm::vec2((float)(j % 8) / 8.0f, (float)(j / 8) / 8.0f);
				_particleColorBuffer[_particleCount] = _particles[i].color;
				_particleCount++;
			}
			_mesh->add(2, GL_FLOAT, 3, (void *)_particlePositionBuffer, _particleCount, GL_STREAM_DRAW);
			_mesh->add(3, GL_FLOAT, 2, (void *)_particleUVBuffer, _particleCount, GL_STREAM_DRAW);
			_mesh->add(4, GL_FLOAT, 4, (void *)_particleColorBuffer, _particleCount, GL_STREAM_DRAW);
			_mesh->setSize(6);
		}

		void    ParticlesSystem::render(void)
		{
			static int	divisor[] {
				0, 0, 1, 1, 1
			};
			glEnable(GL_ALPHA_TEST);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glDepthMask(GL_FALSE);
			Graphics::particleShader->bind();
			Graphics::particleShader->uniformMat(_projectionShaderID, Window::GetInstance()->getProjection3D());
			glm::mat4 view = Camera::main->transform.getMat4(true);
			Graphics::particleShader->uniformMat(_viewShaderID, view);
			glm::mat4 model = transform.getMat4();
			Graphics::particleShader->uniformMat(_modelShaderID, model);
			Graphics::particleShader->uniform1i(_spriteID, 0);
			glActiveTexture(GL_TEXTURE0);
			texture->bind();
			_mesh->render(GL_TRIANGLES, true, _particleCount, (int *)divisor, 5);
			glDepthMask(GL_TRUE);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}


		void	ParticlesSystem::setTexture(Texture *t)
		{
			texture = t;
		}
	}
}