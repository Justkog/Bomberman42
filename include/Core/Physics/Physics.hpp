#ifndef BE_CORE_PHYSICS_HPP
#define BE_CORE_PHYSICS_HPP 1

#include "Core/Core.hpp"
/*!
 * \file Physics.hpp
 * \brief Fonctionnaliter physique du moteur, raycast...
 * \author qhonore, jblondea
 */
namespace BeerEngine
{
	namespace Physics
	{
		/*! \struct Ray
		* \brief Structure des informations du rayon
		*/
		struct Ray
		{
			glm::vec3 origin;
			glm::vec3 direction;
		};
		/*! \struct RaycastHit
		* \brief Structure des informations des objets qui sont rentrer en collision avec un rayson
		*/
		struct RaycastHit
		{
			BeerEngine::Component::ACollider *collider;
			Transform *transform;
			float distance;

			RaycastHit(void) : collider(nullptr), transform(nullptr), distance(0) {}
			RaycastHit(BeerEngine::Component::ACollider *c, Transform *t, float d) : collider(c), transform(t), distance(d) {}

			bool operator<(const RaycastHit &hit) const
			{
				return (distance < hit.distance);
			}
		};
		/*! \class Physics
		* \brief Classe static avec toute les fonctions utilisable sur la physique tel le raycast.
		*/
		class Physics
		{

		public:

			static Ray MouseToWorldRay();
			static Ray ScreenToWorldRay(glm::vec2 screenPosition);

			// Return true if ray collide
			static bool Raycast(glm::vec3 origin, glm::vec3 direction);
			// Return true if ray collide | 'hit' contain datas of the 1st collision
			static bool Raycast(glm::vec3 origin, glm::vec3 direction, RaycastHit &hit);
			// Return true if 'n' < nbCollisions | 'hit' contain datas of the 'n' collision
			static bool Raycast(glm::vec3 origin, glm::vec3 direction, RaycastHit &hit, int n);
			// Return all collisions
			static std::vector<RaycastHit> RaycastAll(glm::vec3 origin, glm::vec3 direction);
			// Return all collisions ordered by distance <
			static std::vector<RaycastHit> RaycastAllOrdered(glm::vec3 origin, glm::vec3 direction);
		};
	}
}

#endif