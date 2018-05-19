#ifndef BE_CORE_COMPONENT_RIGIDBODY2D_HPP
#define BE_CORE_COMPONENT_RIGIDBODY2D_HPP 1
/*!
 * \file RigidBody2D.hpp
 * \brief Component physique
 * \author mgallo
 */
#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
/*! \namespace BeerEngine
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
	/*! \namespace Component
	* espace de nommage regroupant les fonctionnalité des Component du moteur
	*/
	namespace Component
	{
		/*! \class RigidBody2D
		* \brief Permet a un objet ayant se component d'avoir une velociter de s'avoir s'il est deplacable celon une collision et ca mass.
		*/
		class RigidBody2D : public Component
		{
		public:
			glm::vec2	velocity;
			RBType		kinematic;
			float		mass;

		public:

		private: 
			RigidBody2D();
			RigidBody2D(const RigidBody2D &val);
			RigidBody2D &operator=(const RigidBody2D &val);
			
		public:

			RigidBody2D(GameObject *gameObject);
			void    physicUpdate(void);

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif
